#include "dynarr.h"

int initDyna(Dyna* dyna) {
    dyna->head = (iDyna*)malloc(sizeof(iDyna));
    if (dyna->head == NULL) {
        return 2; //no memory left
    }
    dyna->tail = dyna->head;
    dyna->head->val = 0;
    dyna->head->buf = NULL;
    dyna->head->bufsize = 0;
    return 0; //success
}

void exitDyna(Dyna* dyna) {
    iDyna *next;
    while (dyna->head->next != NULL) {
        if (dyna->head->buf != NULL) {
            free(dyna->head->buf);
        }
        next = dyna->head->next;
        free(dyna->head);
        dyna->head = next;
    }
    if (dyna->head->buf != NULL) {
        free(dyna->head->buf);
    }
    free(dyna->head);
}

int appendDyna(Dyna *dyna, void *inbuf, size_t inbufsize, int val) {
    while (dyna->head->next != NULL) {
        dyna->head = dyna->head->next;
    }
    //memory for new dyna node
    dyna->head->next = malloc(sizeof(iDyna));
    if (dyna->head->next == NULL) {
        dyna->head = dyna->tail;
        return 2; //no memory left
    }
    dyna->head = dyna->head->next;
    //buf stuff, if buf NULL then skip
    if (inbuf != NULL) {
        dyna->head->buf = malloc(inbufsize);
        if (dyna->head->buf == NULL && inbufsize != 0) {
            free(dyna->head); //free newly created node
            dyna->head = dyna->tail;
            return 2; //no memory left
        }
        dyna->head->bufsize = inbufsize;
        memcpy(dyna->head->buf, inbuf, inbufsize);
    } else {
        dyna->head->buf = NULL;
        dyna->head->bufsize = 0;
    }
    //initialize value
    dyna->head->val = val;

    dyna->head = dyna->tail;
    return 0;

}

int readDyna(Dyna *dyna, void **inbuf, size_t *inbufsize, int *val, size_t index) {
    size_t cnt = 0;
    while (index != cnt) {
        if (dyna->head->next == NULL) {
            dyna->head = dyna->tail;
            return 1; //list too short(next is null but havent reached index yet)
        }
        dyna->head = dyna->head->next;
        cnt++;
    }
    if (inbuf != NULL) {
        *inbuf = malloc(dyna->head->bufsize);
        if (*inbuf == NULL && dyna->head->bufsize != 0) {
            dyna->head = dyna->tail;
            return 2; //no memory left
        }
        memcpy(*inbuf, dyna->head->buf, dyna->head->bufsize);
        *inbufsize = dyna->head->bufsize;
    }
    *val = dyna->head->val;
    dyna->head = dyna->tail;
    return 0;

} 

int writeDyna(Dyna *dyna, void *inbuf, size_t inbufsize, int val, size_t index) {
    size_t cnt = 0;
    while (index != cnt) {
        if (dyna->head->next == NULL) {
            dyna->head = dyna->tail;
            return 1; //list too short(next is null but havent reached index yet)
        }
        dyna->head = dyna->head->next;
        cnt++;
    }
    dyna->head->buf = malloc(inbufsize);
    if (dyna->head->buf == NULL && inbufsize != 0) {
        dyna->head = dyna->tail;
        return 2; //no memory left
    }
    memcpy(dyna->head->buf, inbuf, inbufsize);
    dyna->head->bufsize = inbufsize;
    dyna->head->val = val;
    dyna->head = dyna->tail;
    return 0;



}

int insertDyna(Dyna *dyna, void* inbuf, size_t inbufsize, int val, size_t index) {
    iDyna *temp, *orig;
    size_t cnt = 0;
    while (index != cnt) {
        if (dyna->head->next == NULL) {
            dyna->head = dyna->tail;
            return 1; //list too short(next is null but havent reached index yet)
        }
        dyna->head = dyna->head->next;
        cnt++;
    }
    temp = dyna->head->next;
    orig = dyna->head;
    dyna->head->next = malloc(sizeof(iDyna));
    if (dyna->head->next == NULL) {
        dyna->head = dyna->tail;
        return 2; //no memory left
    }
    dyna->head = dyna->head->next;
    dyna->head->buf = malloc(inbufsize);
    if (dyna->head->buf == NULL && inbufsize != 0) {
        dyna->head = dyna->tail;
        orig->next = temp;
        return 2; //no memory left
    }
    memcpy(dyna->head->buf, inbuf, inbufsize);
    dyna->head->bufsize = inbufsize;
    dyna->head->val = val;
    dyna->head->next = temp; //connect next with newly created node
    dyna->head = dyna->tail;
    return 0;
    
}

int removeDyna(Dyna* dyna, size_t index) {
    iDyna *temp, *orig;
    size_t cnt = 0;
    if (index == 0) {
        if (dyna->head->next == NULL) {
            return 3; //attempt to remove only list item? XD please use free function
        }
        free(dyna->head->buf);
        dyna->head->next = dyna->head;
        free(dyna->tail);
        dyna->tail = dyna->head;
    }
    while (index - 1 != cnt) {
        if (dyna->head->next == NULL) {
            dyna->head = dyna->tail;
            return 1; //list too short(next is null but havent reached index yet)
        }
        dyna->head = dyna->head->next;
        cnt++;
    }
    orig = dyna->head;
    dyna->head = dyna->head->next;
    free(dyna->head->buf);
    temp = dyna->head->next;
    free(dyna->head);
    orig->next = temp;
    dyna->head = dyna->tail;
    return 0;
}

size_t getDynaLength(Dyna *dyna) {
    size_t cnt = 1;
    while (dyna->head->next != NULL) {
        cnt++;
        dyna->head = dyna->head->next;
    }
    dyna->head = dyna->tail;
    return cnt;
}
