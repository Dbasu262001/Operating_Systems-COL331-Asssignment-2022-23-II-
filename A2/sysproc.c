#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
extern int _sched_policy(int pid,int policy);
extern int _exec_time(int pid,int exec_time);
extern int _deadline(int pid,int deadline);
extern int _rate(int pid,int rate);

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



///Setting sched_policy
int sys_sched_policy(void){
	int pid,policy;
	 if(argint(0, &pid) < 0 || argint(1,&policy)<0)
	 	return -22;
	 //cprintf("%s %d\n","policy : ",policy);
	return _sched_policy(pid,policy);
}

//Setting exec_time
int sys_exec_time(void){
	int pid,exec_time;
	if(argint(0, &pid) < 0 || argint(1,&exec_time)<0)
	 	return -22;
	//cprintf("%s %d\n","exec :",exec_time);
	return _exec_time(pid,exec_time);
}

//Setting deadline
int sys_deadline(void){
	int pid,deadline;
	if(argint(0, &pid) < 0 || argint(1,&deadline)<0)
	 	return -22;
	//cprintf("%s %d\n","deadline : ",deadline);
	return _deadline(pid,deadline);
}

//Setting rate for rms Scheduler
int sys_rate(void){
	int pid,rate;
	if(argint(0, &pid) < 0 || argint(1,&rate)<0)
	 	return -22;
	return _rate(pid,rate);
}
