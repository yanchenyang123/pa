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

#include <isa.h>
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include<assert.h>
#include<common.h>
#include <memory/paddr.h>



enum {
  TK_NOTYPE = 256,
  TK_jia,
  TK_Jian,
  TK_EQ,
  TK_MU,
  TK_DZ,
  TK_Chu,
  TK_Reg,
  TK_zuo,
  TK_you,
  TK_num,
  TK_NQ,
  TK_YU,
  TK_DEREF,
  TK_FU

  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", TK_jia},         // plus
  {"==", TK_EQ},        // equal
  {"(0x).{1,8}", TK_DZ},  //16jinzhi
  {"\\*",TK_MU},          // multiply
  {"\\-",TK_Jian},        //jianfa
  {"\\/",TK_Chu},         //chufa
  {"\\$[^0-9][a-z0-9]+",TK_Reg},         //reg_value
  {"\\(", TK_zuo},
  {"\\)",TK_you},
  {"[1-9][0-9]*",TK_num},
  {"!=", TK_NQ},
  {"&&",TK_YU},
  {"\\*",TK_DEREF},
  
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[1000] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static void substr(char *str_start,int length)
  {
    for(int j=0;j<length;j++)
      {
        tokens[nr_token].str[j]=str_start[j];
      }
  }

static void substr_(char *str_start,int length)
  {
    for(int j=0;j<length-1;j++)
      {
        tokens[nr_token].str[j]=str_start[j+1];
      }
  }

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;


        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
      if(rules[i].token_type==TK_Reg)
        {
          tokens[nr_token].type=rules[i].token_type;
          substr_(substr_start,substr_len);
          nr_token+=1;

          break;
        }
      else
      {
          tokens[nr_token].type=rules[i].token_type;
          substr(substr_start,substr_len);
          nr_token+=1;
      break;
      }

        }


      }
    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }

  }

  return true;
}

bool check_parentheses(int p,int q)
  { 

    int num=0;
    if(tokens[p].type==TK_zuo && tokens[q].type==TK_you)
      {
        num=1;
        for(int i=p+1;i<q;i++)
          {
            if(num==0)
              {
                return false;
              }
            else if(tokens[i].type==TK_zuo)
              {
                num+=1;
              }
            else if(tokens[i].type==TK_you)
              {
                num-=1;
              }
          }
        if(num==1)
          {
            return true;
          }
        if(num!=1)
          {
            assert(0);
          }
      }   
    return false;
        
  }
    
int NBL_ZYSF(int p,int q)
  {
    int index=0;
    for(int i=p;i<=q;i++)
      {
        int num=0;
        if(tokens[i].type==TK_zuo)
          {
            num=1;
            for(int j=i+1;j<=q;j++)
              {
                if(tokens[j].type==TK_zuo)
                  {
                    num+=1;
                  }
                if(tokens[j].type==TK_you)
                  {
                    num-=1;
                  }
                if(num==0)
                  {
                    i=j;
                    break;
                  }
              }
          }

        if(index==0&&(tokens[i].type==TK_Chu||tokens[i].type==TK_MU||tokens[i].type==TK_jia||tokens[i].type==TK_Jian||tokens[i].type==TK_EQ 
        ||tokens[i].type==TK_NQ||tokens[i].type==TK_YU))
          {
            index=i;
          }
        else if(index!=0&&(tokens[i].type==TK_Chu||tokens[i].type==TK_MU||tokens[i].type==TK_jia||tokens[i].type==TK_Jian||tokens[i].type==TK_EQ 
        ||tokens[i].type==TK_NQ||tokens[i].type==TK_YU))
          {
            if(tokens[index].type==TK_YU)
              {
                if(tokens[i].type==TK_YU)
                  {
                    index=i;
                  }
              }
            else if(tokens[index].type==TK_EQ||tokens[index].type==TK_NQ)   
              {
                if(tokens[i].type==TK_YU||tokens[i].type==TK_EQ||tokens[i].type==TK_NQ)
                  {
                    index=i;
                  }
              }
            else if(tokens[index].type==TK_jia||tokens[index].type==TK_Jian)
              {
                if(tokens[i].type==TK_jia||tokens[i].type==TK_Jian||tokens[i].type==TK_YU||tokens[i].type==TK_EQ||tokens[i].type==TK_NQ)
                  {
                    index=i;
                  }
              }
            else if(tokens[index].type==TK_Chu||tokens[index].type==TK_MU)
              {
                index=i;
              }
          }
          

      }
    return index;
  }
paddr_t f(int p,int q)
  { 
      if (p > q) {
          assert(0);
        }
      else if (p == q) 
      {
        int index=0;
        int index1=0;
        switch (tokens[p].type)
          {
            case TK_DZ: 
            {
              index=strtoul(tokens[p].str,NULL,0);
              return index;             
            };
            case TK_Reg:
            {
              _Bool *succese1;
              succese1=(_Bool *)true;
              return -isa_reg_str2val(tokens[p].str,succese1);
            };
            case TK_num:
            {
              sscanf(tokens[p].str,"%d",&index1);
              return index1;
            };
          }
        }
      else if (check_parentheses(p, q) == true) {
        /* The expression is surrounded by a matched pair of parentheses.
        * If that is the case, just throw away the parentheses.
        */
        return f(p + 1, q - 1);
        }
      else if(tokens[p].type==TK_DEREF && NBL_ZYSF(p,q)==0)
        {
          paddr_t val3;
          val3=f(p+1,q);
          return paddr_read(val3,4);
          
        }
      else if(tokens[p].type==TK_FU && NBL_ZYSF(p,q)==0)
        {
          return -f(p+1,q);
        }
      else {
        if(tokens[p].type==TK_NOTYPE)
          {
            return f(p+1,q);
          }
        if(tokens[q].type==TK_NOTYPE)
          {
            return f(p,q-1);
          }
        int op;
        paddr_t val1,val2;
        op=NBL_ZYSF(p,q);
        if(op==0||(op==1&&tokens[0].type==TK_NOTYPE))
          { 
            val1=0;
            val2=f(op+1,q);
          }
        else 

          {
          val1=f(p,op-1);
          val2=f(op+1,q);
          }

        
          switch(tokens[op].type)
            {
            case TK_Chu:return val1/val2;
            case TK_jia:return val1+val2;
            case TK_Jian:return val1-val2;
            case TK_MU: return val1*val2;
            case TK_YU: return val1&&val2;
            case TK_EQ: return val1==val2;
            case TK_NQ: return val1 != val2;
            }
      }
return 0;
  }
paddr_t expr(char *e, bool *success) 
{
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
 for(int i=0;i<nr_token;i++)
      {
        int point =0;
        int point1=0;
        if(tokens[i].type==TK_Jian)
          {
            if(i==0)
              {
                tokens[i].type=TK_FU;
                continue;
              }
            else
              {
                point1=i-1;
              }
            if(tokens[i-1].type==TK_NOTYPE)
              {
                point1=i-2;
              }
            if(point1==-1)
              {
                tokens[i].type=TK_FU;
                continue;
              }
            else if(tokens[point1].type==TK_Chu||tokens[point1].type==TK_jia||tokens[point1].type==TK_Jian||tokens[point1].type==TK_MU||tokens[point1].type==TK_EQ
            ||tokens[point1].type==TK_NQ||tokens[point1].type==TK_YU||tokens[point1].type==TK_zuo||tokens[point1].type==TK_DEREF)
              {
                tokens[i].type=TK_FU;
                continue;
              }
          
        else  
          {
            continue;
          }
          }
        if(tokens[i].type==TK_MU)
          {
            if(i==0)
              {
                tokens[i].type=TK_DEREF;
                continue;
              }
            else  
            {
                point =i-1;
            }
            if(tokens[i-1].type==TK_NOTYPE)
              {
                point -=1;
              }
            if(point==-1)
              {
                tokens[i].type=TK_DEREF;
                continue;

              }
            else if(tokens[point].type==TK_Chu||tokens[point].type==TK_jia||tokens[point].type==TK_Jian||tokens[point].type==TK_MU||tokens[point].type==TK_EQ
            ||tokens[point].type==TK_NQ||tokens[point].type==TK_YU||tokens[point].type==TK_zuo||tokens[point].type==TK_FU)
              {
                tokens[i].type=TK_DEREF;
                continue;
              }
          }
        else  
          {
            continue;
          }
      }
  int p=0;
  int q=nr_token-1;
  /* TODO: Insert codes to evaluate the expression. */
  paddr_t a=f(p,q);
  printf("%u\n",a);
  return a;
}


/* TODO: Implement code to evaluate the expression. */

