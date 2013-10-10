/* This sample file will describe the 2 following functions:
 *  . fabs
 *  . strcmp
*/

#include "cspec/cspec.h"

int main()
{
  CSpec_hRun( fabs );
  CSpec_uRun( fabs );
  CSpec_vRun( fabs );

  CSpec_XmlFileOpen("xml_output.xml", "utf-8");
  CSpec_xRun( fabs );
  CSpec_XmlFileClose();

  CSpec_JUnitXmlFileOpen("junit_xml_output.xml", "utf-8");
  CSpec_jxRun( fabs );
  CSpec_JUnitXmlFileClose();
  return 0;
}

