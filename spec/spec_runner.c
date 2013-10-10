#include <stdio.h>
#include <string.h>

#include "cspec/cspec.h"
#include "cspec/cspec_output_junit_xml.h"
#include "cspec/cspec_output_verbose.h"

define_description(array_new);
define_description(array_delete);
define_description(array_add);
define_description(array_get_element);

define_description(CSpec_NewOutputJUnitXml);
define_description(cspec_output_junit_xml_case1);
define_description(cspec_output_junit_xml_case2);
define_description(destruct_it);
define_description(destruct_descr);

int main()
{
    int ret = 0;

    CSpec_JUnitXmlFileOpen("result.xml", "utf-8");

    ret += CSpec_Run(description(array_new),         CSpec_NewOutputJUnitXml());
    ret += CSpec_Run(description(array_delete),      CSpec_NewOutputJUnitXml());
    ret += CSpec_Run(description(array_add),         CSpec_NewOutputJUnitXml());
    ret += CSpec_Run(description(array_get_element), CSpec_NewOutputJUnitXml());

    CSpec_JUnitXmlFileClose();

    ret += CSpec_Run(description(CSpec_NewOutputJUnitXml),      CSpec_NewOutputVerbose());
    ret += CSpec_Run(description(cspec_output_junit_xml_case1), CSpec_NewOutputVerbose());
    ret += CSpec_Run(description(cspec_output_junit_xml_case2), CSpec_NewOutputVerbose());
    ret += CSpec_Run(description(destruct_it),                  CSpec_NewOutputVerbose());
    ret += CSpec_Run(description(destruct_descr),               CSpec_NewOutputVerbose());

    return ret;
}
