#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
typedef struct 
{
    int ten_san;
    int gio_dat;
    int thgian_thue;
} DatSan;
typedef struct 
{
    DatSan DS[MAX];
    int top;
} Stack;
void init(Stack *stack) 
{
    stack->top = -1;
}
int is_empty(Stack *stack) 
{
    return stack->top == -1;
}
int is_full(Stack *stack) 
{
    return stack->top == MAX - 1;
}
void push(Stack *stack, DatSan DS) 
{
    if (is_full(stack)) 
    {
        printf("Da het san\n");
        return;
    }
    stack->DS[++stack->top] = DS;
}
DatSan pop(Stack *stack) 
{
    if (is_empty(stack)) 
    {
        printf("Khong co lich dat de huy.\n");
        DatSan empty = {-1, -1, -1};
        return empty;
    }
    return stack->DS[stack->top--];
}
int TinhTien(DatSan DS) 
{
    int tien = 0;
    for (int i = 0; i < DS.thgian_thue; i++) 
    {
        if (DS.gio_dat + i < 16) 
        {
            tien += 200000; 
        } else 
        {
            tien += 300000; 
        }
    }
    return tien;
}
void ThongTin(DatSan DS) 
{
    printf("San so: %d, Gio bat dau: %d, Thoi gian: %d gio, Tong tien: %d dong\n",
           DS.ten_san, DS.gio_dat, DS.thgian_thue, TinhTien(DS));
}
void XemTatCa(Stack *stack) 
{
    if (is_empty(stack)) 
    {
        printf("Chua co lich dat san nao!\n");
        return;
    }
    for (int i = stack->top; i >= 0; i--) 
    {
        ThongTin(stack->DS[i]);
    }
}
void heapify(DatSan arr[], int n, int i) 
{
    int largest = i; 
    int left = 2 * i + 1;  
    int right = 2 * i + 2; 

    if (left < n && arr[left].gio_dat > arr[largest].gio_dat)
        largest = left;

    if (right < n && arr[right].gio_dat > arr[largest].gio_dat)
        largest = right;

    if (largest != i) 
    {
        DatSan temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        heapify(arr, n, largest);
    }
}
void heapSort(DatSan arr[], int n) 
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) 
    {
        DatSan temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}
void XemTatCaTheoGio(Stack *stack) 
{
    if (is_empty(stack)) 
    {
        printf("Chua co lich dat san nao!\n");
        return;
    }

    heapSort(stack->DS, stack->top + 1);

    printf("Danh sach dat san theo gio tang dan:\n");
    for (int i = 0; i <= stack->top; i++) 
    {
        ThongTin(stack->DS[i]);
    }
}

int main() 
{
    Stack stack;
    init(&stack);
    int luachon;

    while (1) 
    {
        printf("1. Dat san\n");
        printf("2. Huy san\n");
        printf("3. Hien thi tat ca cac san da dat\n");
        printf("4. Hien thi san da dat theo gio tang dan\n");
        printf("5. Thoat\n");
        printf("Chon yeu cau: ");
        scanf("%d", &luachon);

        if (luachon == 1) 
        {
            DatSan DS;
            printf("Nhap so ID cua san (1 toi 10): ");
            scanf("%d", &DS.ten_san);
            printf("Nhap gio bat dau da (5h -> 23h30): ");
            scanf("%d", &DS.gio_dat);
            printf("Nhap thoi gian thue (gio): ");
            scanf("%d", &DS.thgian_thue);
            push(&stack, DS);
        } 
        else if (luachon == 2) 
        {
            DatSan canceled = pop(&stack);
            if (canceled.ten_san != -1) 
            {
                printf("Da huy san:\n");
                ThongTin(canceled);
            }
        } 
        else if (luachon == 3) 
        {
            XemTatCa(&stack);
        } 
        else if (luachon == 4) 
        {
            XemTatCaTheoGio(&stack);
        } 
        else if (luachon == 5) 
        {
            printf("Thoat chuong trinh.\n");
            break;
        } 
        else 
        {
            printf("Lua chon khong hop le (vui long nhap 1 -> 5).\n");
        }
    }

    return 0;
}
