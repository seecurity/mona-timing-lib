/** fau_timer.c
 *
 * modul to send a request to a web server and measure the time till a response comes back
 *
 * @authors: Niels Iciek, Sebastian Schinzel
 * 
*/


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#define BUFSIZE 1024*1024*10

typedef unsigned long long ticks;

ticks cpu_ticks;			// duration of request in cpu ticks
unsigned long long nano_seconds;	// duration of request in nanoseconds
unsigned long long cpu_speed;		// aprox cpu speed
char *receive_buffer;			// buffer to save the response

/**
 * error
 *
 * function for error messages
 * 
*/
void error(char *msg)
{
	perror(msg);
}

/**
 * get_ticks
 *
 * runs assembly code to get number of cpu ticks 
 * 
 * @return	number of cpu ticks since cpu started
*/
ticks get_ticks()
{
	ticks           ret = 0;
	unsigned long   minor = 0;
	unsigned long   mayor = 0;

	asm             volatile(
                                                 "cpuid \n"
				                 "rdtsc"
				 :               "=a"(minor),
				                 "=d"(mayor)
                                 : "a" (0)
                                 : "%ebx", "%ecx"
	);

	ret = ((((ticks) mayor) << 32) | ((ticks) minor));

	return ret;
}
/** 
 * get_aprox_cpu_speed
 *
 * calculates the current cpu clock speed
 *
 * @return	cpu speed in number of ticks
*/
unsigned long long get_aprox_cpu_speed(){

	unsigned long long speed;
	ticks start_ticks, end_ticks;
	start_ticks = get_ticks();
	sleep(1);
	end_ticks = get_ticks();
	speed = (end_ticks - start_ticks);

	return speed;

}
/**
 * init
 *
 * initializes some values.
 * do this before each sendRequest.
*/
void init(){

	cpu_speed = 0;
	cpu_ticks = 0;
	nano_seconds = 0;
	if(receive_buffer != NULL){
		bzero(receive_buffer, BUFSIZE);
	}
	else{
		receive_buffer = malloc(BUFSIZE);
	}
}

/** 
 * send_request
 *
 * send a request to the given ip adress and port.
 *
 * @param ip Kommandozeilenparameter
 * @param port_no
 * @param request
*/
void send_request(char* ip, int port_no, char* request){
	
	int sockfd, n, len;
	struct hostent *server;
	struct sockaddr_in serv_addr;
	ticks start_ticks, end_ticks;
	
	if(port_no <= 0){
		error("ERROR wrong port number");
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){
		error("ERROR opening socket");
	}
	server = gethostbyname(ip);
	if (server == NULL){
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr,
	      (char *) &serv_addr.sin_addr.s_addr,
	      server->h_length);
	serv_addr.sin_port = htons(port_no);
	if (connect(sockfd, (struct sockaddr *) & serv_addr, sizeof(serv_addr)) < 0){
		error("ERROR connecting");
	}
    	bzero(receive_buffer, BUFSIZE);

	// Write all but the very last byte	
	len = strlen(request);
	n = write(sockfd, request, len - 1);

	// Start the timer...
	start_ticks = get_ticks();
	// Now send the last byte, which also starts processing at server side.
	n = write(sockfd, request + len - 1, 1);
	if (n < 0){
		error("ERROR writing to socket");
	}
	n = read(sockfd, receive_buffer, BUFSIZE - 1);
        // Stop the timer
	end_ticks = get_ticks();
	cpu_ticks = end_ticks - start_ticks;

	close(sockfd);
}

/** 
 * convert_ticks_to_nanosecs
 *
 * calculates how much time in nanoseconds has passed 
 * at given ticks on a cpu with a given frequency
 * saves the result to nano_seconds
 *
 * @param no_ticks	number of cpu ticks 
 * @param speed		cpu speed in Hz
*/
void convert_ticks_to_nanosecs(ticks no_ticks, long long speed){
	
	nano_seconds = (double)no_ticks / (double)speed * 1000000000.0;

}

/** 
 * calculate_time
 *
 * gets current cpu speed and calculates time from cpu ticks and cpu speed
 * 
*/
void calculate_time(){

	cpu_speed = get_aprox_cpu_speed();
	convert_ticks_to_nanosecs(cpu_ticks, cpu_speed); 
	
}

/** 
 * get_response
 *
 * returns the response of the last request
 * 
 * @return	the response of the last request
*/
char* get_response(){

	return receive_buffer;
}

/** 
 * get_cpu_ticks
 *
 * returns the number of cpu ticks the last request has taken
 * 
 * @return	number of cpu ticks
*/
ticks get_cpu_ticks(){

	return cpu_ticks;
}

/** 
 * get_time
 *
 * returns the time in nanoseconds the last request has taken
 * 
 * @return	time in nanoseconds
*/
long long get_time(){

	return nano_seconds;
}

/** 
 * get_speed
 *
 * returns the cpu speed calculated by last calculte_time() call
 * 
 * @return	cpu speed in Hz
*/
unsigned long long get_speed(){

	return cpu_speed;
}

/** 
 * test
 *
 * only for debugging purposes
 *
*/
void test(){
	unsigned long long speed = 0;
	ticks no_ticks = 0;
	long long time = 0;
	char* response = "";
	
	init();
	
	send_request("131.188.31.217", 80, "HEAD / HTTP/1.0\r\n\r\n ");
	calculate_time();
	speed = get_speed();
	no_ticks = get_cpu_ticks();
	time = get_time();
	response = get_response();	
	printf("CPU Speed: %llu\n", speed);
	printf("Ticks: %llu\n", no_ticks);
	printf("Time: %llu Millisec\n", time);
	printf("Response: %s", response);

}

/** 
 * main
 *
 * has no actual function
 *
*/
int main(int argc, char *argv[])
{
	test();


	return 0;
}

