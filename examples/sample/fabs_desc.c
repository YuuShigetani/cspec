#include <math.h>
#include "cspec.h"

describe(fabs, "fabs")

  context("argument is positive")
    it("return positive")
      expect_to_equal(fabs(1.0), 1.0)
      expect_to_equal(fabs(0.0), 0.0)
      expect_to_equal(fabs(6.7), 6.7)
    end
  end

  context("argument is negative")
    it("return positive")
      should_equal(fabs(-1.0), 1.0)
      should_equal(fabs(-6.7), 6.7)
    end
  end

end

