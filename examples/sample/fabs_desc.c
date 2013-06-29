#include <math.h>
#include "cspec.h"

describe(fabs, "標準ライブラリfabsの")

  context("引数が正の時")
    it( "正の数を返す" )
      should_equal( fabs(1.0), 1.0)
      should_equal( fabs(0.0), 0.0)
      should_equal( fabs(6.7), 6.7)
    end
  end

  context("引数が負の時")
    it( "負の数を返す" )
      should_equal( fabs(-1.0), 1.0)
      should_equal( fabs(-6.7), 6.7)
    end
  end

end

