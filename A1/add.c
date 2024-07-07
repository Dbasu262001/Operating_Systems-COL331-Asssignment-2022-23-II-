# include "types.h"
# include "user.h"
# include "date.h"
# include "fcntl.h"
# include "syscall.h"
int main(int argc,char** argv){

printf(1,"%d\n",add(atoi(argv[1]),atoi(argv[2])));
exit();

}

