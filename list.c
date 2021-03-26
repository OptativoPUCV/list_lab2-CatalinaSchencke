#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    const void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(const void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* lista = (List*) malloc (sizeof(List));
  lista->head = NULL;
  lista->tail = NULL;
  lista->current =NULL;
  return lista;
}

void * firstList(List * list) {
  list->current=list->head;
    return ((void*)list->head->data);
}

void * nextList(List * list) {
  if (list->current!=NULL){
      if (list->current->next!=NULL){
      list->current=list->current->next;
      
      return ((void*)(list->current->data));
    }
    else{
      return NULL;
    }
  }
  else{
    return NULL;
  }
  
  
}

void * lastList(List * list) {
    list->current=list->tail;
    return ((void*)(list->current->data));
}

void * prevList(List * list) {
  if(list->current!=NULL){
    if(list->current->prev!=NULL){
    list->current=list->current->prev;
    return ((void*)(list->current->data));
    }
  }
  return NULL;
}

void pushFront(List * list, const void * data) {
  Node* nuevoNodo = createNode((void*)data);
  if (list->head!=NULL){
    list->head->prev = nuevoNodo;
    nuevoNodo->next =list->head;
    list->head=nuevoNodo;
  }
  else{
    list->head=nuevoNodo;
    list->tail=nuevoNodo;
  }


}

void pushBack(List * list, const void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, const void * data) {
  
  if(list->current!=NULL){
    Node* nuevoNodo = createNode((void*)data);
    if (list->current->next!=NULL){
      list->current->next->prev=nuevoNodo;
      nuevoNodo->next=list->current->next->prev;
      list->current->next=nuevoNodo;
      nuevoNodo->prev=list->current;
    }
    else{
      list->current->next=nuevoNodo;
      nuevoNodo->prev=list->current;
      list->tail=nuevoNodo;
    }
  }
  else{
    pushFront(list, data);
  }
  
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
   Node* nuevoNodo = createNode((void*)(list->current->data));
    if(list->current!=NULL){
      if (list->current->next!=NULL){
        if (list->current->prev!=NULL){
          list->current->prev->next=list->current->next;
          list->current->next->prev=list->current->prev;
        }
        else{
          list->head=list->current->next;
          list->head->prev=NULL;
        }
        list->current=nuevoNodo->next;
      }
      else{
        if (list->current->prev!=NULL){
          list->tail=list->current->prev;
          list->tail->next=NULL;
        }
        else{
          list->head=NULL;
          list->tail=NULL;
        }
      }
  }
  return nuevoNodo;
    
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}