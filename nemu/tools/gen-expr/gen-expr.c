/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include<stdlib.h>
#include<unistd.h>
// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";
static int m=0;
static int choose(int n)
  {

    int a=rand()%n;
    return a;
  }
static int mo0()
  {
    for(int i=m-1;i>=0;i--)
      {
        if(buf[i]==' ')
          continue;
        else
          {
            if(buf[i]=='/')
              {
                return 1;
              }
            else
              {
                return 0;
              }
          }
      }
    return 0;
  }
static void gen_num()
  {
    int a=rand()%100;
    char b[4];
    sprintf(b,"%d",a);
    if(b[0]=='0')
      {
        int x=mo0();
        if(x==1)
          b[0]='1';
      }
    for(int i=0;b[i]!='\0';i++)
      {
        buf[m]=b[i];
        m+=1;
        buf[m]='\0';
      }
    }


static void gen(char a)
  {
    buf[m]=a;
    m+=1;
  }
static void gen_rand_op()
  {
    switch(choose(4))
      {
        case 0:buf[m]='+',m+=1;break;
        case 1:buf[m]='-',m+=1;break;
        case 2:buf[m]='*',m+=1;break;
        case 3:buf[m]='/',m+=1;break;
      }
  }
static void gen_kongge()
  {
    buf[m]=' ';
    m+=1;
  }  
static void gen_rand_expr() {
  switch(choose(4))
    {
      case 0:gen_num();break;
      case 1:gen('(');gen_rand_expr();gen(')');break;
      case 2:gen_rand_expr();gen_rand_op();gen_rand_expr();break;
      case 3:gen_kongge();gen_rand_expr();break;
    }
  buf[m]='\0';

}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    m=0;
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    fscanf(fp, "%d", &result);
    pclose(fp);
    if(result>=0&&result<=65535)
    {
    printf("%u %s\n", result, buf);
    }

  }
  return 0;
}
