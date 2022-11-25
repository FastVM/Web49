#define LIMIT_SQUARED 4.0
#define MAXIMUM_ITERATIONS 50

#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  const uint64_t image_Width_And_Height =
      (__builtin_expect(atoi(argv[1]), 15000) + 7) / 8 * 8;

  uint8_t *const pixels =
      malloc(image_Width_And_Height * image_Width_And_Height / 8);

  double initial_r[image_Width_And_Height], initial_i[image_Width_And_Height];
  for (uint64_t xy = 0; xy < image_Width_And_Height; xy++) {
    initial_r[xy] = 2.0 / image_Width_And_Height * xy - 1.5;
    initial_i[xy] = 2.0 / image_Width_And_Height * xy - 1.0;
  }

  for (uint64_t y = 0; y < image_Width_And_Height; y++) {
    const double prefetched_Initial_i = initial_i[y];
    for (uint64_t x_Major = 0; x_Major < image_Width_And_Height; x_Major += 8) {

      double pixel_Group_r[8], pixel_Group_i[8];
      for (uint64_t x_Minor = 0; x_Minor < 8; x_Minor++) {
        pixel_Group_r[x_Minor] = initial_r[x_Major + x_Minor];
        pixel_Group_i[x_Minor] = prefetched_Initial_i;
      }

      uint8_t eight_Pixels = 0xff;

      int iteration = MAXIMUM_ITERATIONS;
      do {
        uint8_t current_Pixel_Bitmask = 0x80;
        for (uint64_t x_Minor = 0; x_Minor < 8; x_Minor++) {
          const double r = pixel_Group_r[x_Minor];
          const double i = pixel_Group_i[x_Minor];

          pixel_Group_r[x_Minor] = r * r - i * i + initial_r[x_Major + x_Minor];
          pixel_Group_i[x_Minor] = 2.0 * r * i + prefetched_Initial_i;

          if (r * r + i * i > LIMIT_SQUARED)
            eight_Pixels &= ~current_Pixel_Bitmask;

          current_Pixel_Bitmask >>= 1;
        }
      } while (eight_Pixels && --iteration);

      pixels[y * image_Width_And_Height / 8 + x_Major / 8] = eight_Pixels;
    }
  }

  fprintf(stdout, "P4\n%" PRIu64 " %" PRIu64 "\n", image_Width_And_Height,
          image_Width_And_Height);
  fwrite(pixels, image_Width_And_Height * image_Width_And_Height / 8, 1,
         stdout);

  free(pixels);

  return 0;
}
