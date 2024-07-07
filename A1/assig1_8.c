#include "types.h"
#include "stat.h"
#include "user.h"
int
main(int argc, char *argv[])
{
	if(argc< 2){
		printf(1,"Need type and input filename\n");
		exit();
	}
	char *filename;
	filename=argv[2];
	int type = atoi(argv[1]);
	printf(1,"Type is %d and filename is %s\n",type, filename);

	int tot_sum = 0;	

	int size=1000;
	short arr[size];
	char c;
	int fd = open(filename, 0);
	for(int i=0; i<size; i++){
		read(fd, &c, 1);
		arr[i]= c - '0';
		read(fd, &c, 1);
	}	
  	close(fd);
  	// this is to supress warning
  	printf(1,"first elem %d\n", arr[0]);
  
  	//----FILL THE CODE HERE for unicast sum
	int pid;
	int start_ind;
	int end_ind;
	int C_pids[8];
	int my_pid = getpid();
	for(int i=0;i<8;i++){
		pid = fork();
		if(pid!=0){
			C_pids[i] = pid;
		}else{
			start_ind = i*(size/8);
			if(i!=7){
			
			end_ind = (i+1)*(size/8);
			
			}else{
			//start_ind = 
			end_ind = size;
			}
			
			break;
		}
	
	}
	//int mypid =getpid();
	if(type ==0){
		if(pid==0){
			int p_sum = 0;
			for(int i=start_ind;i<end_ind;i++)
			{
				p_sum += arr[i];
				//printf(1,"index is %d value is %d :",i,arr[i]);
			}
			int *msg_child = (int *)malloc(8);
			msg_child = &p_sum;
			send(getpid(),my_pid,(void*)msg_child);
			free(msg_child);
			exit();
		
		}
		else{
			for(int i=0;i<8;i++){
				int stat =-1;
				char *msg = (char *)malloc(8);
				while(stat==-1){
					 stat = recv(msg);
				 }
				int* t = (int*) msg;
				tot_sum = tot_sum + *t;
				free(msg);
				
				
			}
			for(int i=0;i<8;i++){
				wait();
			}
		}
	
	
	
	

	}

  	//------------------

  	if(type==0){ //unicast sum
		printf(1,"Sum of array for file %s is %d\n", filename,tot_sum);
	}
	//Multicast Distributed algorithm
	if(type ==1){
		
		if(pid==0){//Child process
			int p_sum = 0;
			for(int i=start_ind;i<end_ind;i++)
			{
				p_sum += arr[i];
				//printf(1,"index is %d value is %d :",i,arr[i]);
			}
			int *msg_child = (int *)malloc(8);
			msg_child = &p_sum;
			send(getpid(),my_pid,(void*)msg_child);
			int st_p = -1;
			char *c_msg = (char*)malloc(8);
			while(st_p ==-1){
				st_p = recv(c_msg);
			}
			float* p_mean = (float*)c_msg;
			float mean = *p_mean;
			float sum_to =0.0;
			for(int i=start_ind;i<end_ind;i++)
			{
				sum_to = sum_to + (mean - (float)arr[i])*(mean - (float)arr[i]);
			}
			float* st = (float*)malloc(8);
			st = &sum_to;
			char* s_msg = (char*)st;
			//int cv = (int)mean;
			//int stpp = (int) sum_to;
			//printf(1,"cv %d stpp %d \n",cv,stpp);
			send(getpid(),my_pid,(void*)s_msg);
			free(msg_child);
			free(c_msg);
			free(st);
			
			exit();
		
		}
		else{
			for(int i=0;i<8;i++){
				int stat =-1;
				char *msg = (char *)malloc(8);
				while(stat==-1){
					 stat = recv(msg);
				 }
				int* t = (int*) msg;
				tot_sum = tot_sum + *t;
				
				
			}
			printf(1," total sum %d :",tot_sum);
			float C_mean = (float)tot_sum/1000.0;
			float* mm = (float*)malloc(8);
			mm = &C_mean;
			send_multi(getpid(),C_pids,(void*)mm);
			int r =-1;
			float Variance = 0.0;
			char* n_msg = (char*)malloc(8);
			for(int i=0;i<8;i++){
				r=-1;
				while(r==-1){
					r = recv(n_msg);
				}
				float* V_temp = (float*)n_msg;
				Variance = Variance + *V_temp;
				//printf(1,"ggg %d",(int)*V_temp);
				
			}			
			Variance = Variance / (float)size;
			int beg=(int)(Variance);
			int fin=(int)(Variance*100)-beg*100;
 			printf(1, "Variance of array for the file arr is %d.%d \n", beg, fin);
 			free(n_msg);
 			free(mm);
			for(int i=0;i<8;i++){
				wait();
			}
		}
		
	
	}
	
	
	exit();
}
