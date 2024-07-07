# include "types.h"
# include "user.h"
# include "date.h"
# include "fcntl.h"
# include "stat.h"
int
main ( int argc , char * argv [])
{
// If you follow the naming convention , the system
//call
// name will be sys_toggle and you
// call it by calling the function toggle ();
// toggle ();
int x = toggle();
printf(1,"Current Trace is(0 for TRACE_ON,1 for TRCAE_OFF) %d",x);
exit () ;
}
