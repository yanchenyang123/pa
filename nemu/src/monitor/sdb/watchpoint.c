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

#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;
  char *e;
  paddr_t old_number;
  bool if_is_open;

  /* TODO: Add more members if necessary */

} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;
void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
    wp_pool[i].e=NULL;
    wp_pool[i].old_number=0;
    wp_pool[i].if_is_open=0;
  }

  head = NULL;
  free_ = wp_pool;
}
WP* new_wp(char *exp)
  {
    int t=-1;
    for(int i=0;i<NR_WP;i++)
      {
        if(wp_pool[i].if_is_open==0)
          {
            if(i==0)
              {
                wp_pool[0].e=exp;
                wp_pool[0].if_is_open=1;
                wp_pool[0].old_number=expr(exp,(_Bool *)true);
                head=&wp_pool[0];
                free_=&wp_pool[1];
                t=0;
                break;
              }
            else
              {
                wp_pool[i].e=exp;
                wp_pool[i].old_number=expr(exp,(_Bool *)true);
                wp_pool[i].if_is_open=1;
                free_=&wp_pool[i+1];
                t=i;
                break;

              }

          }
      }
    if(t==-1)
      {
        assert(0);
      }
    return &wp_pool[t];
  }
void free_wp(int i)
  {
    wp_pool[i].if_is_open=0;
    wp_pool[i].e=NULL;
    wp_pool[i].old_number=0;

    
  }
void p_all_points()
  {
    for(int i=0;i<NR_WP;i++)
      {
        printf("wp_pool %d  %d   %s\n",i,wp_pool[i].old_number,wp_pool[i].e);
      }
  }


/* TODO: Implement the functionality of watchpoint */

