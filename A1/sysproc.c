#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

extern int send(int sender_pid, int rec_pid, void *msg);
extern int send_multi(int sender_pid, int rec_pids[], void *msg);
extern int recv(void *msg);
enum trace Current_Trace = TRACE_OFF;
int call_count[28]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


int sys_send_multi(void){
	int sender_pid;
	char* msg;
	int* rec_pids;
	if(argint(0,&sender_pid) < 0 || argstr(2,&msg) < 0 || argptr(1,(void*)&rec_pids,sizeof(*rec_pids)) < 0){
		cprintf("Invalid Arguments");
		return -1;
	}
	send_multi(sender_pid,rec_pids,(void*)msg);

return 0;
}
//Sys send function
int sys_send(void)
{
	int sender_pid,rec_pid;
	char *msg;
	if(argint(0,&sender_pid) < 0 || argint(1,&rec_pid) <0 || argstr(2,&msg) < 0){
		cprintf("Invalid Arguments");
		return -1;
	} 

	send(sender_pid,rec_pid,(void*)msg);
	return 0;
}

//SYs_recv function

int sys_recv(void)
{
	char* msg;
	if(argstr(0,&msg) <0){
		cprintf("Invalid Arguments");
 	return -1;
 	}
	
	//if(!msg) return -1;
	return recv((void *)msg);
}



int add(int a,int b){
 return a +b;
}
//System Call Add
int sys_add(void)
{
   int a,b;
   if(argint(0,&a) <0 ||  argint(1,&b) <0){
   return -1;
  
   }

   return add(a,b);
   
}
//System Call ps


// System call added by me sys_toggle
int 
sys_toggle(void)
{
    if(Current_Trace == TRACE_OFF){
    	Current_Trace = TRACE_ON;
    	for(int i=0;i<28;i++){
    	call_count[i]=0;
    	}
    }
    else{
    	Current_Trace = TRACE_OFF;
    }
   // printf("current_trace = %d",Current_Trace);
return Current_Trace;
}



int
sys_print_count(void)
{
//atic int temp[22];
int c_fork    = call_count[0];
int c_exit    = call_count[1];
int c_wait    = call_count[2];
int c_pipe    = call_count[3];
int c_read    = call_count[4];
int c_kil     = call_count[5];
int c_exec    = call_count[6];
int c_fstat   = call_count[7];
int c_chdir   = call_count[8];
int c_dup     = call_count[9];
int c_getpid  = call_count[10];
int c_sbrk    = call_count[11];
int c_sleep   = call_count[12];
int c_uptime  = call_count[13];
int c_open    = call_count[14];
int c_write   = call_count[15];
int c_mknod   = call_count[16];
int c_unlink  = call_count[17];
int c_link    = call_count[18];
int c_mkdir   = call_count[19];
int c_close   = call_count[20];
//int c_toggle  = call_count[21];
//int c_pt_count  = call_count[22];
int c_add     = call_count[23]; 
int c_ps      = call_count[24];
int c_send    = call_count[25]; 
int c_recv    = call_count[26];   
int c_multi_send  = call_count[27]; 



/////////////////////////////////////////
if(c_add >0){
  cprintf("%s %d\n","SYS_add",c_add);
}
if(c_chdir >0){
  cprintf("%s %d\n","SYS_chdir",c_chdir);
}
if(c_close >0){
   cprintf("%s %d\n","SYS_close",c_close);
}
if(c_dup >0){
   cprintf("%s %d\n","SYS_dup",c_dup);
}
if(c_exec >0){
   cprintf("%s %d\n","SYS_exec",c_exec);
}
if(c_exit >0){
   cprintf("%s %d\n","SYS_exit",c_exit);
}
if(c_fork >0){
   cprintf("%s %d\n","SYS_fork",c_fork);
}
if( c_fstat>0){
   cprintf("%s %d\n","SYS_fstat",c_fstat);
}
if(c_getpid >0){
   cprintf("%s %d\n","SYS_getpid",c_getpid);
}
if(c_kil >0){
   cprintf("%s %d\n","SYS_kill",c_kil);
}
if(c_link >0){
   cprintf("%s %d\n","SYS_link",c_link);
}
if( c_mkdir>0){
   cprintf("%s %d\n","SYS_mkdir",c_mkdir);
}
if( c_mknod>0){
   cprintf("%s %d\n","SYS_mknod",c_mknod);
}

if(c_open >0){
   cprintf("%s %d\n","SYS_open",c_open);
}
if( c_pipe>0){
   cprintf("%s %d\n","SYS_pipe",c_pipe);
}
if(c_ps >0){
  cprintf("%s %d\n","SYS_ps",c_ps);
}
/*if( c_pt_count>0){
   cprintf("%s %d\n","SYS_print_count",c_pt_count);
}*/
if( c_read>0){
   cprintf("%s %d\n","SYS_read",c_read);
}
if(c_recv >0){
  cprintf("%s %d\n","SYS_recv",c_recv);
}
if( c_sbrk>0){
   cprintf("%s %d\n","SYS_sbrk",c_sbrk);
}
if(c_send >0){
  cprintf("%s %d\n","SYS_send",c_send);
}
if(c_multi_send >0){
  cprintf("%s %d\n","SYS_send_multi",c_multi_send);
}
if( c_sleep>0){
   cprintf("%s %d\n","SYS_sleep",c_sleep);
}
/*if(c_toggle >0){
   cprintf("%s %d\n","SYS_toggle",c_toggle);
}*/
if( c_unlink>0){
   cprintf("%s %d\n","SYS_unlink",c_unlink);
}
if( c_uptime>0){
   cprintf("%s %d\n","SYS_uptime",c_uptime);
}
if(c_wait >0){
   cprintf("%s %d\n","SYS_wait",c_wait);
}
if( c_write>0){
   cprintf("%s %d\n","SYS_write",c_write);
}

return 23;
}





int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
