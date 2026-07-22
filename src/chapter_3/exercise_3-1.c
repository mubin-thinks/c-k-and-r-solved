#include <stdio.h>
#include <time.h>

#define SEARCH_ARRAY_LENGTH 100
#define SEARCHING_ARRAY_LENGTH 50
#define SPACES_FOR_A_TAB "        "

int binary_search(int x, int v[], int n);
int binary_search_k_and_r(int x, int v[], int n);

int main() {
        // clock_t has arrived from the `time.h` header
        // file. We can sorround binary search computation
        // with clock() function to get the running time of
        // the search.
        clock_t start_time, end_time;
        int search_array[SEARCH_ARRAY_LENGTH] = {
                12, 17, 21, 37, 44, 58, 61, 63, 76, 84, 85, 92, 110, 119, 129, 134,
                145, 148, 152, 167, 168, 187, 198, 214, 233, 238, 240, 245, 252, 264, 271,
                281, 289, 316, 319, 326, 362, 375, 390, 390, 403, 405, 413, 438, 451, 456,
                468, 479, 482, 494, 517, 520, 531, 534, 543, 566, 574, 581, 599, 609, 640,
                648, 655, 676, 691, 693, 698, 701, 706, 712, 729, 735, 750, 759, 768, 773,
                801, 811, 824, 827, 843, 847, 855, 864, 880, 882, 891, 904, 907, 926, 935,
                957, 965, 972, 980, 993
        };
        int searching_array[SEARCHING_ARRAY_LENGTH] = {
                614, 29, 887, 167, 758, 103, 492, 816, 257, 680, 145, 931, 364, 570, 218,
                799, 56, 472, 908, 133, 625, 362, 751, 19, 390, 397, 562, 170, 986, 435,
                691, 248, 774, 12, 519, 360, 947, 126, 603, 411, 839, 295, 735, 51, 982,
                337, 664, 214, 890, 473
        };
        for (int i = 0, search_result; i < SEARCHING_ARRAY_LENGTH; i++) {
                printf("{\n");
                start_time = clock();
                search_result = binary_search_k_and_r(
                        searching_array[i],
                        search_array,
                        SEARCH_ARRAY_LENGTH
                );
                end_time = clock();
                printf(
                        "%sbinary_search_k_and_r: result: %d, runtime: %fs\n",
                        SPACES_FOR_A_TAB,
                        search_result,
                        (double)(end_time - start_time) / CLOCKS_PER_SEC
                );
                start_time = clock();
                search_result = binary_search(
                        searching_array[i],
                        search_array,
                        SEARCH_ARRAY_LENGTH
                );
                end_time = clock();
                printf(
                        "%sbinary_search: result: %d, runtime: %fs\n",
                        SPACES_FOR_A_TAB,
                        search_result,
                        (double)(end_time - start_time) / CLOCKS_PER_SEC
                );
                printf("}\n");
        }
        return 0;
}

int binary_search(int x, int v[], int n) {
        int l = 0, r = n - 1, mid;
        while (l <= r) {
                mid = (l + r) / 2;
                if (x < v[mid]) r = mid - 1;
                else l = mid + 1;
        }
        if (v[r] == x) return r;
        return -1;
}

int binary_search_k_and_r(int x, int v[], int n) {
        int low, high, mid;
        low = 0;
        high = n - 1;
        while (low <= high) {
                mid = (low + high) / 2;
                if (x < v[mid])
                        high = mid - 1;
                else if (x > v[mid])
                        low = mid + 1;
                else
                        return mid;
        }
        return -1;
}
