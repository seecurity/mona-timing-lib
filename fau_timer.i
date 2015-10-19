/* File : fau_timer.i */
%module fau_timer
%include "cdata.i"
%{
typedef unsigned long long ticks;
extern ticks cpu_ticks;
extern unsigned long long nano_seconds;
extern unsigned long long cpu_speed;
extern char *receive_buffer;
extern void error(char *msg);
extern ticks get_ticks();
extern unsigned long long get_aprox_cpu_speed();
extern void init();
extern void send_request(char* ip, int port_no, char* request, size_t length);
extern void convert_ticks_to_nanosecs(ticks no_ticks, long long speed);
extern void calculate_time();
extern void* get_response();
extern ticks get_cpu_ticks();
extern unsigned long long get_time();
extern unsigned long long get_speed();
extern int get_len_read();
extern void test();
extern int main(int argc, char *argv[]);
%}

typedef unsigned long long ticks;
extern ticks cpu_ticks;
extern unsigned long long nano_seconds;
extern unsigned long long cpu_speed;
extern char *receive_buffer;
extern void error(char *msg);
extern ticks get_ticks();
extern unsigned long long get_aprox_cpu_speed();
extern void init();
extern void send_request(char* ip, int port_no, char* request, size_t length);
extern void convert_ticks_to_nanosecs(ticks no_ticks, long long speed);
extern void calculate_time();
extern void* get_response();
extern ticks get_cpu_ticks();
extern unsigned long long get_time();
extern unsigned long long get_speed();
extern int get_len_read();
extern void test();
extern int main(int argc, char *argv[]);
