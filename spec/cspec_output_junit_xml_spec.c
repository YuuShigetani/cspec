#include <stdio.h>
#include <stdlib.h>
#include "cspec/cspec.h"
#include "cspec/cspec_output_junit_xml.h"
#include "cspec/cspec_private_output_junit_xml.h"

describe(CSpec_NewOutputJUnitXml, "CSpecOutputStruct* CSpec_NewOutputJUnitXml()")
    it("returns not-NULL pointer")
        should_not_be_null(CSpec_NewOutputJUnitXml())
    end

    it("returns the struct which member is setted up")
        should_not_be_null(CSpec_NewOutputJUnitXml()->startDescribeFun)
        should_not_be_null(CSpec_NewOutputJUnitXml()->endDescribeFun)
        should_not_be_null(CSpec_NewOutputJUnitXml()->startItFun)
        should_not_be_null(CSpec_NewOutputJUnitXml()->endItFun)
        should_not_be_null(CSpec_NewOutputJUnitXml()->evalFun)
        should_not_be_null(CSpec_NewOutputJUnitXml()->pendingFun)
        should_equal(CSpec_NewOutputJUnitXml()->failed, 0)
    end
end

FILE* fp;
void before_fun(const char* const fname)
{
    fp = fopen(fname, "r");
}
void check(const char* const expect)
{
    if (NULL == fp) {
        should_pending("file not opened");
    }
    else {
        char buffer[1024];
        char* p;

        p = fgets(buffer, sizeof(buffer), fp);
        if (NULL == p) {
            should_pending("EOF");
        }
        else {
            should_match(buffer, expect);
        }
    }
}
void after()
{
    if (NULL == fp) {
        return;
    }
    fclose(fp);
}

describe(cspec_output_junit_xml_case1, "when 1 description with 1 'it' and 1 assertion done, 1 success")
    CSpecOutputStruct* output_struct;
    const char* const fname = "output_cspec_output_junit_xml_case1.xml";

    output_struct = CSpec_NewOutputJUnitXml();
    CSpec_JUnitXmlFileOpen(fname, "utf-8");
    startDescribeFunJUnitXml("descr1");
    startItFunJUnitXml("it1");
    evalFunJUnitXml("fname", 100, "assertion1", 1);
    endItFunJUnitXml();
    endDescribeFunJUnitXml();
    CSpec_JUnitXmlFileClose();

    before_fun(fname);
    it("output header")
        check("<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n");
    end
    it("output testsuites start tag")
        check("<testsuites>\n");
    end
    it("output testsuite start tag with error=0, failure=0, tests=1")
        check("  <testsuite errors=\"0\" failures=\"0\" name=\"descr1\" tests=\"1\">\n");
    end
    it("output testcase with assertion=1")
        check("    <testcase name=\"it1\" assertions=\"1\">\n");
        check("    </testcase>\n");
    end
    it("output testsuite end tag")
        check("  </testsuite>\n");
    end
    it("output testsuites end tag")
        check("</testsuites>\n");
    end
    after();
end

describe(cspec_output_junit_xml_case2, "when 2 description with 3 'it' and 4 assertion done, 2 success and 1 failure and 1 pending")
    CSpecOutputStruct* output_struct;
    const char* const fname = "output_cspec_output_junit_xml_case2.xml";

    output_struct = CSpec_NewOutputJUnitXml();
    CSpec_JUnitXmlFileOpen(fname, "shift-jis");
    startDescribeFunJUnitXml("descr1");
    startItFunJUnitXml("it1-1");
    evalFunJUnitXml("fname", 11, "assertion1", 1);
    endItFunJUnitXml();
    startItFunJUnitXml("it1-2");
    evalFunJUnitXml("fname", 12, "assertion2", 0);
    endItFunJUnitXml();
    endDescribeFunJUnitXml();
    startDescribeFunJUnitXml("descr2");
    startItFunJUnitXml("it2-1");
    evalFunJUnitXml("fname", 21, "assertion3", 1);
    pendingFunJUnitXml("reason");
    endItFunJUnitXml();
    endDescribeFunJUnitXml();
    CSpec_JUnitXmlFileClose();

    before_fun(fname);
    it("output header")
        check("<?xml version=\"1.0\" encoding=\"shift-jis\" ?>\n");
    end
    it("output testsuites start tag")
        check("<testsuites>\n");
    end
    it("output testsuite start tag with error=0, failure=1, tests=2")
        check("  <testsuite errors=\"0\" failures=\"1\" name=\"descr1\" tests=\"2\">\n");
    end
    it("output testcase with assertion=1")
        check("    <testcase name=\"it1-1\" assertions=\"1\">\n");
        check("    </testcase>\n");
    end
    it("output testcase with assertion=1, failure=1")
        check("    <testcase name=\"it1-2\" assertions=\"1\">\n");
        check("      <failure message=\"Failed\" type=\"\">\n");
        check("fname:12: assertion2\n");
        check("      </failure>\n");
        check("    </testcase>\n");
    end
    it("output testsuite end tag")
        check("  </testsuite>\n");
    end
    it("output testsuite start tag with error=0, failure=0, tests=1")
        check("  <testsuite errors=\"0\" failures=\"0\" name=\"descr2\" tests=\"1\">\n");
    end
    it("output testcase with assertion=0")
        check("    <testcase name=\"it2-1\" assertions=\"0\">\n");
        check("    </testcase>\n");
    end
    it("output testsuite end tag")
        check("  </testsuite>\n");
    end
    it("output testsuites end tag")
        check("</testsuites>\n");
    end
    after();
end

describe(destruct_it, "void destruct_it(itOutputs_t* const it)")
    it("do nothing when 'it' is null")
        destruct_it(NULL);
        should_be_true(1)
    end

    it("free 'it->failures' and 'it->descr'")
        itOutputs_t it;

        it.descr = malloc(8);
        if (NULL == it.descr) {
            should_pending("malloc failed")
        }
        it.failures = array_new(1);
        if (NULL == it.failures) {
            should_pending("array_new failed")
        }
        destruct_it(&it);
        should_be_null(it.descr)
        should_be_null(it.failures)
    end
end

describe(destruct_descr, "void destruct_descr(descrOutputs_t* const descr)")
    it("do nothing when 'descr' is null")
        destruct_descr(NULL);
        should_be_true(1)
    end

    it("free 'descr->descr' and 'descr->it'")
        descrOutputs_t descr;

        descr.descr = malloc(1);
        descr.itOutputs = malloc(sizeof(itOutputs_t));
        if (NULL == descr.itOutputs) {
            should_pending("malloc failed")
        }
        descr.n_itOutputs = 1;
        descr.itOutputs[0].descr = malloc(1);
        if (NULL == descr.itOutputs[0].descr) {
            should_pending("malloc failed")
        }
        descr.itOutputs[0].failures = array_new(1);
        if (NULL == descr.itOutputs[0].failures) {
            should_pending("array_new failed")
        }
        destruct_descr(&descr);
        should_be_null(descr.descr)
        should_equal(0, descr.n_itOutputs)
        should_be_null(descr.itOutputs)
    end
end
