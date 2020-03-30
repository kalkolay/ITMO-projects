#pragma once

#if defined(__GNUC__)
#define UNLIKELY(x) __builtin_expect(x, 0)
#elif defined(__clang__) && !defined(__c2__) && defined(__has_builtin)
#if __has_builtin(__builtin_expect)
#define UNLIKELY(x) __builtin_expect(x, 0)
#endif
#endif

#ifndef UNLIKELY
#define UNLIKELY(expr) (expr)
#endif // !UNLIKELY

#define area _width * _height

const unsigned short PGM = 5, MAX_COLORS = 255;

const double ORDERED_MATRIX[8][8] =
        {
                {0. / 64.,  48. / 64., 12. / 64., 60. / 64., 3. / 64.,  51. / 64., 15. / 64., 63. / 64.},
                {32. / 64., 16. / 64., 44. / 64., 28. / 64., 35. / 64., 19. / 64., 47. / 64., 31. / 64.},
                {8. / 64.,  56. / 64., 4. / 64.,  52. / 64., 11. / 64., 59. / 64., 7. / 64.,  55. / 64.},
                {40. / 64., 24. / 64., 36. / 64., 20. / 64., 43. / 64., 27. / 64., 39. / 64., 23. / 64.},
                {2. / 64.,  50. / 64., 14. / 64., 62. / 64., 1. / 64.,  49. / 64., 13. / 64., 61. / 64.},
                {34. / 64., 18. / 64., 46. / 64., 30. / 64., 33. / 64., 17. / 64., 45. / 64., 29. / 64.},
                {10. / 64., 58. / 64., 6. / 64.,  54. / 64., 9. / 64.,  57. / 64., 5. / 64.,  53. / 64.},
                {42. / 64., 26. / 64., 38. / 64., 22. / 64., 41. / 64., 25. / 64., 37. / 64., 21. / 64.}
        };

const double JJN_MATRIX[3][5] = { {0, 0, 0, 7, 5}, {3, 5, 7, 5, 3}, {1, 3, 5, 3, 1} };

const double SIERRA3_MATRIX[3][5] = { {0, 0, 0, 5, 3}, {2, 4, 5, 4, 2}, {0, 2, 3, 2, 0} };

const double ATKINSON_MATRIX[3][5] = { {0, 0, 0, 1, 1},{0, 1, 1, 1, 0},{0, 0, 1, 0, 0} };

const double HALFTONE_MATRIX[4][4] =
        {
                {13. / 16., 11. / 16., 4. / 16.,  8. / 16.},
                {6. / 16.,  0,         3. / 16.,  15. / 16.},
                {14. / 16., 1. / 16.,  2. / 16.,  7. / 16.},
                {9. / 16.,  5. / 16.,  10. / 16., 12. / 16.},
        };

enum Dithering
{
    NoDithering = 0,
    OrderedDithering,
    RandomDithering,
    FloydSteinbergDithering,
    JarvisJudiceNinkeDithering,
    Sierra3Dithering,
    AtkinsonDithering,
    HalftoneDithering
};