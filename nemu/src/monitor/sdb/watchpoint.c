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


  /* TODO: Add more members if necessary */

} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;
static int index_=0;
void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
    wp_pool[i].e=NULL;
  }

  head = NULL;
  free_ = wp_pool;
}
WP* new_wp(char *expr)
  {
    WP* node=NULL;
    WP* node_nul=NULL;
    if(index_==32)
      {
        assert(0);
      }
    node=&wp_pool[index_];
    node->e=expr;
    node->next=node_nul;
    index_+=1;
    free_=free_->next;
    if(head==NULL)
      {
        head=node;
      }
    else 
      {
        WP* pa =head;
        while(head->next!=NULL)
          {
            head=head->next;
          }
        head->next=node;
        head=pa;
      }
    return node;
     
  }
void free_wp(WP *wp)
  {
    WP *pa=head;
    
    while (head->next!=wp&&head->next!=NULL)
    {
      head=head->next;
      if(head->next==NULL)
        {
          assert(0);
        }
    }
    free_=head->next;
    index_-=1;
    head->next=NULL;
    head=pa;
  }


/* TODO: Implement the functionality of watchpoint */

