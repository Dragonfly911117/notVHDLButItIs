#include <stdio.h>
int main(){
  char buf[1024] = "Data Input 123456 hello world";
  FILE* fp = fopen("/dev/demo","w+");
  if (fp ==NULL){
    printf("cannot open device\n");
    return -1;
  }
  fwrite(buf, sizeof(buf), 1, fp);
  fread(buf, sizeof(buf), 1, fp);
  fclose(fp);
  return 0;
}