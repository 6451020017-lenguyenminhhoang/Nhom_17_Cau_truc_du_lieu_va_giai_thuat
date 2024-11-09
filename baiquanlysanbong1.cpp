#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30  // so luong san 30
#define MAX_CUSTOMERS 100  // so luong khach hang
typedef struct 
{
    int ma_san;
    char ten_san[50];
    char loai_san[20];  // loai san trong nha và ngoai troi
} SanBong;

typedef struct 
{
    SanBong danh_sach[MAX];
    int so_luong;
} DanhSachSanBong;

typedef struct 
{
    int ten_san;
    int gio_dat;
    float thgian_thue;
    int so_luong_nuoc;  // so nuoc
    int thue_ao;        // 1 thuê ao, 0 khong
    char sdt[15];       // so dien thoai khach hang
} DatSan;

typedef struct 
{
    DatSan DS[MAX];
    int top;
} Stack;

typedef struct 
{
    char sdt[15];
    char ten_khach_hang[50];
    char lich_su_dat_san[500];  // lich su dat san
    char danh_gia[200];         // danh gia phan hoi
} KhachHang;

typedef struct 
{
    KhachHang danh_sach[MAX_CUSTOMERS];
    int so_luong;
} DanhSachKhachHang;

// Khoi tao ngan xep
void init(Stack *stack) 
{
    stack->top = -1;
}

// Kiem tra ngan xep rong
int is_empty(Stack *stack) 
{
    return stack->top == -1;
}

// Kiem tra ngan xep day
int is_full(Stack *stack) 
{
    return stack->top == MAX - 1;
}

//day phan tu vao ngan xep
void push(Stack *stack, DatSan DS) 
{
    if (is_full(stack)) 
	{
        printf("Da het san\n");
        return;
    }
    stack->DS[++stack->top] = DS;
}

// lay phan tu ra khoi ngan xep
DatSan pop(Stack *stack) 
{
    if (is_empty(stack)) 
	{
        printf("Khong co lich dat da huy.\n");
        DatSan empty = {-1, -1, -1, 0, 0, ""};
        return empty;
    }
    return stack->DS[stack->top--];
}

// Tinh tien
int TinhTien(DatSan DS, DanhSachSanBong *ds) 
{
    int tien = 0;
    for (float i = 0; i < DS.thgian_thue; i++) 
	{
        if (DS.gio_dat + i < 16) 
		{
            tien += 200000;
        } 
		else 
		{
            tien += 300000;
        }
    }

    // Tìm loai sân
    char loai_san[20];
    for (int i = 0; i < ds->so_luong; i++) 
	{
        if (ds->danh_sach[i].ma_san == DS.ten_san) 
		{
            strcpy(loai_san, ds->danh_sach[i].loai_san);
            break;
        }
    }

    // Thêm pphu phi 10% neu la san trong nha
    if (strcmp(loai_san, "trong nha") == 0) 
	{
        tien += tien * 0.1;
    }

    // Thêm chi phi dich vu
    tien += DS.so_luong_nuoc * 8000;
    if (DS.thue_ao) 
	{
        tien += 20000;
    }

    return tien;
}

// In thông tin sân
void ThongTin(DatSan DS, DanhSachSanBong *ds) 
{
    printf("San so: %d, Gio da: %d, Thoi gian: %.1f gio, SL nuoc: %d, Thue ao: %s, Tong tien: %d dong\n",
           DS.ten_san, DS.gio_dat, DS.thgian_thue, DS.so_luong_nuoc, DS.thue_ao ? "Co" : "Khong", TinhTien(DS, ds));
}

// Xem tat ca lich dat
void XemTatCa(Stack *stack, DanhSachSanBong *ds) 
{
    if (is_empty(stack)) 
	{
        printf("Chua co lich dat san nao!\n");
        return;
    }
    for (int i = stack->top; i >= 0; i--) 
	{
        ThongTin(stack->DS[i], ds);
    }
}

// Tao thanh heap tai i
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

// Sap xep mang theo gio bat dau tang dan
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

// In ra tat ca lich dat theo gio bat dau tang dan
void XemTatCaTheoGio(Stack *stack, DanhSachSanBong *ds) 
{
    if (is_empty(stack)) 
	{
        printf("chua co lich dat san nao!\n");
        return;
    }

    heapSort(stack->DS, stack->top + 1);

    printf("Danh sach dat san theo gio tang dan:\n");
    for (int i = 0; i <= stack->top; i++) 
	{
        ThongTin(stack->DS[i], ds);
    }
}

// Khoi tao danh sách sân bóng
void khoi_tao_danh_sach(DanhSachSanBong *ds) 
{
    ds->so_luong = 0;
}

// Thêm sân bóng vào dau danh sách
void them_san_bong_dau(DanhSachSanBong *ds, SanBong san) 
{
    if (ds->so_luong < MAX) 
	{
        for (int i = ds->so_luong; i > 0; i--) 
		{
            ds->danh_sach[i] = ds->danh_sach[i - 1];
        }
        ds->danh_sach[0] = san;
        ds->so_luong++;
    } 
	else 
	{
        printf("Danh sach da day!\n");
    }
}

// Thêm sân bóng vào cuoi danh sách
void them_san_bong_cuoi(DanhSachSanBong *ds, SanBong san) 
{
    if (ds->so_luong < MAX) 
	{
        ds->danh_sach[ds->so_luong++] = san;
    } 
	else 
	{
        printf("Danh sach da day!\n");
    }
}

// Thêm sân bóng vào vi trí K cua danh sách
void them_san_bong_vi_tri(DanhSachSanBong *ds, SanBong san, int k) 
{
    if (ds->so_luong < MAX && k >= 0 && k <= ds->so_luong) 
	{
        for (int i = ds->so_luong; i > k; i--) 
		{
            ds->danh_sach[i] = ds->danh_sach[i - 1];
        }
        ds->danh_sach[k] = san;
        ds->so_luong++;
    } 
	else 
	{
        printf("vi tri ko hop le!\n");
    }
}

// Xóa sân bóng o dau danh sach
void xoa_san_bong_dau(DanhSachSanBong *ds) 
{
    if (ds->so_luong > 0) 
	{
        for (int i = 0; i < ds->so_luong - 1; i++) 
		{
            ds->danh_sach[i] = ds->danh_sach[i + 1];
        }
        ds->so_luong--;
        printf("da xoa \n");
    } 
	else 
	{
        printf("Danh sach rong!\n");
    }
}

// Xóa sân bóng o cuoi danh sách
void xoa_san_bong_cuoi(DanhSachSanBong *ds) 
{
    if (ds->so_luong > 0) 
	{
        ds->so_luong--;
        printf("da xoa\n");
    } 
	else 
	{
        printf("Danh sach rong!\n");
    }
 }   
// Xóa sân bóng o vi tri K cua danh sach
void xoa_san_bong_vi_tri(DanhSachSanBong *ds, int k) 
{
    if (ds->so_luong > 0 && k >= 0 && k < ds->so_luong) 
	{
        for (int i = k; i < ds->so_luong - 1; i++) 
		{
            ds->danh_sach[i] = ds->danh_sach[i + 1];
        }
        ds->so_luong--;
        printf("Da xoa san bong o vi tri %d\n", k);
    } 
	else 
	{
        printf("vi tri khng hop le!\n");
    }
}

// Tìm kiem san bong trong danh sach
void tim_kiem_san_bong(DanhSachSanBong *ds, int ma_san) 
{
    for (int i = 0; i < ds->so_luong; i++) 
	{
        if (ds->danh_sach[i].ma_san == ma_san) 
		{
            printf("Ma san: %d, Ten san: %s, Loai san: %s\n",
                   ds->danh_sach[i].ma_san, ds->danh_sach[i].ten_san,
                   ds->danh_sach[i].loai_san);
            return;
        }
    }
    printf("khong tim thay san bong co ma %d\n", ma_san);
}

// sap xep danh sách sân bóng theo ma sân
void sap_xep_theo_ma(DanhSachSanBong *ds) 
{
    for (int i = 0; i < ds->so_luong - 1; i++) 
	{
        for (int j = i + 1; j < ds->so_luong; j++) 
		{
            if (ds->danh_sach[i].ma_san > ds->danh_sach[j].ma_san) 
			{
                SanBong temp = ds->danh_sach[i];
                ds->danh_sach[i] = ds->danh_sach[j];
                ds->danh_sach[j] = temp;
            }
        }
    }
}

// Liet kê danh sách sân bóng
void liet_ke_san_bong(DanhSachSanBong *ds) 
{
    if (ds->so_luong == 0) 
	{
        printf("Danh sach trong!\n");
        return;
    }
    for (int i = 0; i < ds->so_luong; i++) 
	{
        printf("Ma san: %d, Ten san: %s, Loai san: %s\n",
               ds->danh_sach[i].ma_san, ds->danh_sach[i].ten_san,
               ds->danh_sach[i].loai_san);
    }
}

// Khoi tao danh sách khách hàng
void khoi_tao_danh_sach_khach_hang(DanhSachKhachHang *dskh) 
{
    dskh->so_luong = 0;
}

// Thêm khách hàng vào danh sách
void them_khach_hang(DanhSachKhachHang *dskh, KhachHang kh) 
{
    if (dskh->so_luong < MAX_CUSTOMERS) 
	{
        dskh->danh_sach[dskh->so_luong++] = kh;
    } 
	else 
	{
        printf("Danh sach khach hang da day!\n");
    }
}

// Tìm kiem khach hang theo sdt
KhachHang* tim_kiem_khach_hang(DanhSachKhachHang *dskh, char *sdt) 
{
    for (int i = 0; i < dskh->so_luong; i++) 
	{
        if (strcmp(dskh->danh_sach[i].sdt, sdt) == 0) 
		{
            return &dskh->danh_sach[i];
        }
    }
    return NULL;
}

// cap nhap lich su dat san cua khach hang
void cap_nhat_lich_su(KhachHang *kh, DatSan DS) 
{
    char lich_su[100];
    sprintf(lich_su, "San so: %d, Gio da: %d, Thoi gian: %.1f gio\n", DS.ten_san, DS.gio_dat, DS.thgian_thue);
    strcat(kh->lich_su_dat_san, lich_su);
}

// Gui thong bao nhac nho
void gui_thong_bao(char *sdt, char *thong_bao) 
{
    printf("Gui thong bao den %s: %s\n", sdt, thong_bao);
}

// Ðánh gia phan hoi
void danh_gia_phan_hoi(KhachHang *kh, char *danh_gia) 
{
    strcpy(kh->danh_gia, danh_gia);
}
void cap_nhat_thong_tin_khach_hang(KhachHang *kh, char *ten_moi, char *sdt_moi) 
{
    strcpy(kh->ten_khach_hang, ten_moi);
    strcpy(kh->sdt, sdt_moi);
    printf("Da cap nhat thong tin khach hang.\n");
}
void hien_thi_dat_san(Stack *stack, char *sdt) 
{
    int found = 0;
    for (int i = 0; i <= stack->top; i++) 
	{
        if (strcmp(stack->DS[i].sdt, sdt) == 0) 
		{
            printf("Thong tin dat san cua %s:\n", sdt);
            printf("San so: %d, Gio dat: %d, Thoi gian: %.1f gio, SL nuoc: %d, Thue ao: %s\n",
                   stack->DS[i].ten_san, stack->DS[i].gio_dat, stack->DS[i].thgian_thue, stack->DS[i].so_luong_nuoc,
                   stack->DS[i].thue_ao ? "Co" : "Khong");
            found = 1;
            break;
        }
    }
    if (!found) 
	{
        printf("Khong co lich dat cho khach hang nay.\n");
    }
}
void xem_tat_ca_phan_hoi(DanhSachKhachHang *dskh) 
{
    printf("Tat ca cac phan hoi cua khach hang:\n");
    for (int i = 0; i < dskh->so_luong; i++) {
        printf("Khach hang %s (%s): %s\n", dskh->danh_sach[i].ten_khach_hang,
               dskh->danh_sach[i].sdt, dskh->danh_sach[i].danh_gia);
    }
}
int main() 
{
    DanhSachSanBong ds;
    khoi_tao_danh_sach(&ds);

    Stack stack;
    init(&stack);

    DanhSachKhachHang dskh;
    khoi_tao_danh_sach_khach_hang(&dskh);

    int lua_chon;

    while (1) 
	{
        printf("1. Them san bong\n");
        printf("2. Xoa san bong\n");
        printf("3. Tim kiem san bong\n");
        printf("4. Sap xep san bong theo ma\n");
        printf("5. Liet ke san bong\n");
        printf("6. Dat san\n");
        printf("7. Huy san\n");
        printf("8. Hien thi tat ca cac san da dat\n");
        printf("9. Hien thi san da dat theo gio tang dan\n");
        printf("10. Them khach hang\n");
        printf("11. Tim kiem khach hang\n");
        printf("12. Gui thong bao nhac nho\n");
        printf("13. Danh gia phan hoi\n");
        printf("14. Cap nhat thong tin khach hang\n");
        printf("15. Hien thi lich dat cua khach hang\n");
        printf("16. Xem tat ca phan hoi khach hang\n");
        printf("17. Them san bong vao dau danh sach\n");
        printf("18. Them san bong vao cuoi danh sach\n");
        printf("19. Them san bong vao vi tri K\n");
        printf("20. Xoa san bong o dau danh sach\n");
        printf("21. Xoa san bong o cuoi danh sach\n");
        printf("22. Xoa san bong o vi tri K\n");
        printf("23. Thoat\n");
        printf("Chon yeu cau: ");
        scanf("%d", &lua_chon);

        if (lua_chon == 1) 
		{
            SanBong san;
            printf("Nhap ma san: ");
            scanf("%d", &san.ma_san);
            printf("Nhap ten san: ");
            scanf("%s", san.ten_san);
            printf("Nhap loai san (trong nha / ngoai troi): ");
            scanf("%s", san.loai_san);
            them_san_bong_cuoi(&ds, san);
        } 
		else if (lua_chon == 2) 
		{
            int ma_san;
            printf("Nhap ma san can xoa: ");
            scanf("%d", &ma_san);
            xoa_san_bong_vi_tri(&ds, ma_san);
        } 
		else if (lua_chon == 3) 
		{
            int ma_san;
            printf("Nhap ma san can tim: ");
            scanf("%d", &ma_san);
            tim_kiem_san_bong(&ds, ma_san);
        } 
		else if (lua_chon == 4) 
		{
            sap_xep_theo_ma(&ds);
            printf("Da sap xep san bong theo ma.\n");
        } 
		else if (lua_chon == 5) 
		{
            liet_ke_san_bong(&ds);
        } 
		else if (lua_chon == 6) 
		{
            DatSan DS;
            printf("Nhap so ID cua san (1 - 30): ");
            scanf("%d", &DS.ten_san);
            printf("Nhap gio dat: ");
            scanf("%d", &DS.gio_dat);
            printf("Nhap thoi gian thue (gio): ");
            scanf("%f", &DS.thgian_thue);
            printf("Nhap so luong nuoc: ");
            scanf("%d", &DS.so_luong_nuoc);
            printf("Thue ao (1: Co, 0: Khong): ");
            scanf("%d", &DS.thue_ao);
            printf("Nhap so dien thoai: ");
            scanf("%s", DS.sdt);
            push(&stack, DS);

            KhachHang *kh = tim_kiem_khach_hang(&dskh, DS.sdt);
            if (kh != NULL) 
			{
                cap_nhat_lich_su(kh, DS);
            } 
			else 
			{
                printf("Khach hang khong ton tai!\n");
            }
        } 
		else if (lua_chon == 7) 
		{
            DatSan DS = pop(&stack);
            if (DS.ten_san != -1) 
			{
                printf("Da huy lich dat san so %d\n", DS.ten_san);
            }
        } 
		else if (lua_chon == 8) 
		{
            XemTatCa(&stack, &ds);
        } 
		else if (lua_chon == 9) 
		{
            XemTatCaTheoGio(&stack, &ds);
        } 
		else if (lua_chon == 10) 
		{
            KhachHang kh;
            printf("Nhap ten khach hang: ");
            scanf("%s", kh.ten_khach_hang);
            printf("Nhap so dien thoai: ");
            scanf("%s", kh.sdt);
            them_khach_hang(&dskh, kh);
        } 
		else if (lua_chon == 11) 
		{
            char sdt[15];
            printf("Nhap so dien thoai khach hang: ");
            scanf("%s", sdt);
            KhachHang *kh = tim_kiem_khach_hang(&dskh, sdt);
            if (kh != NULL) 
			{
                printf("Ten khach hang: %s\n", kh->ten_khach_hang);
                printf("Lich su dat san: %s\n", kh->lich_su_dat_san);
                printf("Danh gia: %s\n", kh->danh_gia);
            } 
			else 
			{
                printf("Khach hang khong ton tai!\n");
            }
        } 
		else if (lua_chon == 12) 
		{
            char sdt[15];
            char thong_bao[100];
            printf("Nhap so dien thoai khach hang: ");
            scanf("%s", sdt);
            printf("Nhap noi dung thong bao: ");
            scanf(" %[^\n]", thong_bao);
            gui_thong_bao(sdt, thong_bao);
        } 
		else if (lua_chon == 13) 
		{
            char sdt[15];
            char danh_gia[200];
            printf("Nhap so dien thoai khach hang: ");
            scanf("%s", sdt);
            KhachHang *kh = tim_kiem_khach_hang(&dskh, sdt);
            if (kh != NULL) 
			{
                printf("Nhap danh gia: ");
                scanf(" %[^\n]", danh_gia);
                danh_gia_phan_hoi(kh, danh_gia);
            } 
			else 
			{
                printf("Khach hang khong ton tai!\n");
            }
        } 
		else if (lua_chon == 14) 
		{
            char sdt[15], ten_moi[50], sdt_moi[15];
            printf("Nhap so dien thoai khach hang: ");
            scanf("%s", sdt);
            KhachHang *kh = tim_kiem_khach_hang(&dskh, sdt);
                        if (kh != NULL) 
						{
                printf("Nhap ten moi: ");
                scanf("%s", ten_moi);
                printf("Nhap so dien thoai moi: ");
                scanf("%s", sdt_moi);
                cap_nhat_thong_tin_khach_hang(kh, ten_moi, sdt_moi);
            } 
			else 
			{
                printf("Khach hang khong ton tai!\n");
            }
        } 
		else if (lua_chon == 15) 
		{
            char sdt[15];
            printf("Nhap so dien thoai khach hang de xem lich dat: ");
            scanf("%s", sdt);
            hien_thi_dat_san(&stack, sdt);
        } 
		else if (lua_chon == 16) 
		{
            xem_tat_ca_phan_hoi(&dskh);
        } 
	    else if (lua_chon == 17) 
		{
            SanBong san;
            printf("Nhap ma san: ");
            scanf("%d", &san.ma_san);
            printf("Nhap ten san: ");
            scanf("%s", san.ten_san);
            printf("Nhap loai san (trong nha / ngoai troi): ");
            scanf("%s", san.loai_san);
            them_san_bong_dau(&ds, san);
        } 
		else if (lua_chon == 18) 
		{
            SanBong san;
            printf("Nhap ma san: ");
            scanf("%d", &san.ma_san);
            printf("Nhap ten san: ");
            scanf("%s", san.ten_san);
            printf("Nhap loai san (trong nha / ngoai troi): ");
            scanf("%s", san.loai_san);
            them_san_bong_cuoi(&ds, san);
        } else if (lua_chon == 19) {
            SanBong san;
            int k;
            printf("Nhap ma san: ");
            scanf("%d", &san.ma_san);
            printf("Nhap ten san: ");
            scanf("%s", san.ten_san);
            printf("Nhap loai san (trong nha / ngoai troi): ");
            scanf("%s", san.loai_san);
            printf("Nhap vi tri K: ");
            scanf("%d", &k);
            them_san_bong_vi_tri(&ds, san, k);
        } 
		else if (lua_chon == 20) 
		{
            xoa_san_bong_dau(&ds);
        } 
		else if (lua_chon == 21) 
		{
            xoa_san_bong_cuoi(&ds);
        } 
		else if (lua_chon == 22) 
		{
            int k;
            printf("Nhap vi tri K: ");
            scanf("%d", &k);
            xoa_san_bong_vi_tri(&ds, k);
        }
        else if (lua_chon == 23) 
		{
            printf("Ket thuc chuong trinh.\n");
            break;
        } 
		else 
		{
            printf("Lua chon khong hop le!\n");
        }
    }

    return 0;
}



