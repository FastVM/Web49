#define PREFERRED_NUMBER_OF_BLOCKS_TO_USE 12

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  const int n = atoi(argv[1]);

  int factorial_Lookup_Table[n + 1];
  factorial_Lookup_Table[0] = 1;
  for (int i = 0; ++i <= n;) {
    factorial_Lookup_Table[i] = i * factorial_Lookup_Table[i - 1];
  }

  const int block_Size =
      factorial_Lookup_Table[n] /
      (factorial_Lookup_Table[n] < PREFERRED_NUMBER_OF_BLOCKS_TO_USE
           ? 1
           : PREFERRED_NUMBER_OF_BLOCKS_TO_USE);

  int maximum_Flip_Count = 0, checksum = 0;

#pragma omp parallel for \
     reduction(max:maximum_Flip_Count) reduction(+:checksum)
  for (int initial_Permutation_Index_For_Block = 0;
       initial_Permutation_Index_For_Block < factorial_Lookup_Table[n];
       initial_Permutation_Index_For_Block += block_Size) {

    int count[n];
    int8_t temp_Permutation[n], current_Permutation[n];

    count[0] = 0;
    for (int i = 0; i < n; ++i)
      current_Permutation[i] = i;
    for (int i = n - 1, permutation_Index = initial_Permutation_Index_For_Block;
         i > 0; --i) {
      const int d = permutation_Index / factorial_Lookup_Table[i];
      permutation_Index = permutation_Index % factorial_Lookup_Table[i];
      count[i] = d;

      for (int j = 0; j < n; ++j)
        temp_Permutation[j] = current_Permutation[j];
      for (int j = 0; j <= i; ++j)
        current_Permutation[j] = j + d <= i ? temp_Permutation[j + d]
                                            : temp_Permutation[j + d - i - 1];
    }

    const int last_Permutation_Index_In_Block =
        initial_Permutation_Index_For_Block + block_Size - 1;
    for (int permutation_Index = initial_Permutation_Index_For_Block;;
         ++permutation_Index) {

      if (current_Permutation[0] > 0) {

        for (int i = 0; ++i < n;) {
          temp_Permutation[i] = current_Permutation[i];
        }

        int flip_Count = 1;

        for (int first_Value = current_Permutation[0];
             temp_Permutation[first_Value] > 0; ++flip_Count) {

          const int8_t new_First_Value = temp_Permutation[first_Value];
          temp_Permutation[first_Value] = first_Value;

          if (first_Value > 2) {
            int low_Index = 1, high_Index = first_Value - 1;
            do {
              const int8_t temp = temp_Permutation[high_Index];
              temp_Permutation[high_Index] = temp_Permutation[low_Index];
              temp_Permutation[low_Index] = temp;
            } while (low_Index++ + 3 <= high_Index-- && low_Index < 16);
          }

          first_Value = new_First_Value;
        }

        if (permutation_Index % 2 == 0) {
          checksum += flip_Count;
        } else {
          checksum -= flip_Count;
        }

        if (flip_Count > maximum_Flip_Count)
          maximum_Flip_Count = flip_Count;
      }

      if (permutation_Index >= last_Permutation_Index_In_Block) {
        break;
      }

      int8_t first_Value = current_Permutation[1];
      current_Permutation[1] = current_Permutation[0];
      current_Permutation[0] = first_Value;
      for (int i = 1; ++count[i] > i;) {
        count[i++] = 0;
        const int8_t new_First_Value = current_Permutation[0] =
            current_Permutation[1];

        for (int j = 0; ++j < i;) {
          current_Permutation[j] = current_Permutation[j + 1];
        }

        current_Permutation[i] = first_Value;
        first_Value = new_First_Value;
      }
    }
  }

  printf("%d\nPfannkuchen(%d) = %d\n", checksum, n, maximum_Flip_Count);

  return 0;
}
