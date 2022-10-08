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
  paddr_t new_number;

  /* TODO: Add more members if necessary */

} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;
int index_=0;
void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
    wp_pool[i].e=NULL;
    wp_pool[i].old_number=0;
    wp_pool[i].new_number=0;
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
    node=free_;
    node->e=expr;
    free_=free_->next;
    node->next=node_nul;
    node->new_number=0;
    node->old_number=0;
    index_+=1;

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
      assert(head->next!=NULL);
    }
    WP *node=head->next;
    head->next=node->next;
    node->next=free_->next;
    free_=node;
    head=pa;
    
  }
void p_all_points()
  {
    for(int i=0;i<NR_WP;i++)
      {
        printf("wp_pool %d  %d   %s\n",i,wp_pool[i].old_number,wp_pool[i].e);
      }
  }


/* TODO: Implement the functionality of watchpoint */

