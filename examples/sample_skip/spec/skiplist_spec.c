#include "cspec/cspec.h"
#include "../src/skip_list.h"

describe(EmptySkipList, "Empty skip list")

  SkipSet* ss = make_skipset();

  it( "has a count of 0" )
    should_equal(count(ss), 0)
  end

  it( "does not contain any value" )
    should_equal(contains(ss, 0), 0)
    should_equal(contains(ss, 1), 0)
    should_equal(contains(ss, 2), 0)
    should_equal(contains(ss, -1), 0)
  end

  it( "fails when deleting nodes" )
    should_equal(delete(ss, 0), 0)
    should_equal(delete(ss, 2), 0)
    should_equal(delete(ss, 5), 0)
  end

  delete_skipset(ss);

end

describe(SkipListCount, "count")

  SkipSet* ss = make_skipset();

  it( "returns 0 when the list is empty" )
    should_equal(count(ss), 0)
  end

  it( "returns 1 when one element has been inserted" )
    insert(ss, 0);
    should_equal(count(ss), 1)
  end

  it( "returns the number of different elements" )
    insert(ss, 1);
    insert(ss, 2);
    insert(ss, 0);
    should_equal(count(ss), 3)
  end

  delete_skipset(ss);

end

describe(SkipListInsert, "insert")

  SkipSet* ss = make_skipset();

  it( "returns 1 when insertion is successful" )
    should_equal( insert(ss, 0), 1)
  end

  it( "returns 0 when insertion failed (item already in the list)" )
    insert(ss, 255);
    should_equal( insert(ss, 255), 0)

    should_pending("check with a more complex list (several levels)")
  end

  delete_skipset(ss);

end

describe(SkipListContains, "contains")

  SkipSet* ss = make_skipset();

  it( "returns 1 when the item is found" )
    insert(ss, 45);
    should_equal( contains(ss, 45), 1)
  end

  it( "returns 0 when the item is not found" )
    should_equal( contains(ss, -45), 0)
  end

  delete_skipset(ss);

end

describe(SkipListDelete, "delete")

  SkipSet* ss = make_skipset();

  it( "returns 1 when the item is successfully deleted" )
    insert(ss, 45);
    should_equal( delete(ss, 45), 1)
  end

  it( "returns 0 when the item is not found" )
    should_equal( delete(ss, 45), 0)
  end

  delete_skipset(ss);

end
