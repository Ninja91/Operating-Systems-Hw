#include <ts_disptb.h>

/* Initializing the TS scheduler priority datat structure */
struct ts_disptb tsdtab[NOF_PRIOIRITIES] = {
    {0, 17, 200},/* Prioirity 0*/
    {0, 17, 200},/* Prioirity 1*/
    {0, 17, 200},/* Prioirity 2*/
    {0, 17, 160},/* Prioirity 3*/
    {1, 17, 160},/* Prioirity 4*/
    {2, 17, 160},/* Prioirity 5*/
    {3, 17, 160},/* Prioirity 6*/
    {4, 17, 120},/* Prioirity 7*/
    {5, 17, 120},/* Prioirity 8*/
    {6, 17, 120},/* Prioirity 9*/
    {7, 17, 80},/* Prioirity 10*/
    {8, 18, 80},/* Prioirity 11*/
    {9, 18, 80},/* Prioirity 12*/
    {10, 18, 40},/* Prioirity 13*/
    {11, 18, 40},/* Prioirity 14*/
    {12, 19, 40},/* Prioirity 15*/
    {13, 19, 40},/* Prioirity 16*/
    {14, 19, 40},/* Prioirity 17*/
    {15, 19, 40},/* Prioirity 18*/
    {16, 19, 40},/* Prioirity 19*/
};
