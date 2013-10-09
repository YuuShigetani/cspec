#include <math.h>
#include <stdlib.h>
#include "cspec/cspec.h"

int n = 0;
describe(fabs, "fabs")

  context("argument is zero")
    it("return zero")
      expect_to_equal(fabs(n), n)
    end
  end

  before(make_random_number)
    n = rand();
  end

  context("argument is positive")
    it("return positive")
      expect_to_equal(fabs(n), n)
    end
  end

  context("argument is negative")
    it("return positive")
      expect_to_equal(fabs(-n), n)
    end
  end

end
