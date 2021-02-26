#ifndef HELPERS_ASSERT_H
#define HELPERS_ASSERT_H

#define ASSERT_CATCH_INPUT_ERROR(some_code)                                    \
  try {                                                                        \
    some_code;                                                                 \
    ASSERT_TRUE(false) << "torrent::input_error not caught";                   \
  } catch (torrent::input_error & e) {                                         \
  }

#endif
