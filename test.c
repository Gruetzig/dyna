#include "dyna.h"

void printAllVals(Dyna *dyna) {
    char printbuf[2000];
    sprintf(printbuf, "list:");
    while (dyna->head->next != NULL) {
        sprintf(printbuf, "%s %d", printbuf, dyna->head->val);
        dyna->head = dyna->head->next;
    }
    sprintf(printbuf, "%s %d", printbuf, dyna->head->val);
    dyna->head = dyna->tail;
    printf("%s\n", printbuf);
}

int main() {
    printf("hello\n");
    Dyna dyna;
    int ret;
    ret = initDyna(&dyna);
    if (ret) {
        printf("initDyna fail, %d\n", ret);
    } else {
        printf("initDyna success \n");
    }
    printf("getDynaLength ret %d\n", getDynaLength(&dyna));
    ret = writeDyna(&dyna, NULL, 0, 3, 0);
    if (ret) {
        printf("writeDyna fail, %d\n", ret);
    } else {
        printf("writeDyna success \n");
    }
    size_t bs;
    int read;
    ret = readDyna(&dyna, NULL, &bs, &read, 0);
    if (ret) {
        printf("readDyna fail, %d\n", ret);
    } else {
        printf("readDyna success \n");
    }
    printf("readDyna ret %d\n", read);
    ret = appendDyna(&dyna, NULL, 0, 4);
    if (ret) {
        printf("appendDyna fail, %d\n", ret);
    } else {
        printf("appendDyna success \n");
    }
    printf("getDynaLength ret %d\n", getDynaLength(&dyna));
    ret = readDyna(&dyna, NULL, &bs, &read, 1);
    if (ret) {
        printf("readDyna fail, %d\n", ret);
    } else {
        printf("readDyna success \n");
    }
    printf("readDyna ret %d\n", read);
    ret = appendDyna(&dyna, NULL, 0, 8);
    if (ret) {
        printf("appendDyna fail, %d\n", ret);
    } else {
        printf("appendDyna success \n");
    }
    printAllVals(&dyna);
    exitDyna(&dyna);
    printf("exitdyna success\n");
    return 0;
}