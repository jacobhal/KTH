<?xml version="1.0"?>
<xsl:stylesheet version="1.0" 
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
	xmlns:ss="urn:schemas-microsoft-com:office:spreadsheet">

	<xsl:template match="CourseList">
		<ss:Workbook>
			<ss:Worksheet ss:Name="Sheet1">
        <ss:Table>
        	<ss:Column ss:Width="100"/>
        	<!-- Row for headers -->
        	<ss:Row>
            <ss:Cell>
              <ss:Data ss:Type="String">Namn</ss:Data>
            </ss:Cell>
            <ss:Cell>
              <ss:Data ss:Type="String">Kurskod</ss:Data>
            </ss:Cell>
            <ss:Cell>
              <ss:Data ss:Type="String">Läsår</ss:Data>
            </ss:Cell>
            <ss:Cell>
              <ss:Data ss:Type="String">Period 1</ss:Data>
            </ss:Cell>
            <ss:Cell>
              <ss:Data ss:Type="String">Period 2</ss:Data>
            </ss:Cell>
            <ss:Cell>
              <ss:Data ss:Type="String">Period 3</ss:Data>
            </ss:Cell>
            <ss:Cell>
              <ss:Data ss:Type="String">Period 4</ss:Data>
            </ss:Cell>
          </ss:Row>
          <xsl:apply-templates/>
        </ss:Table>
    </ss:Worksheet>
		</ss:Workbook>
	</xsl:template>

	<xsl:template match="Course">
		<ss:Row>
			<ss:Cell>
        <ss:Data ss:Type="String"><xsl:value-of select="Name"/></ss:Data>
      </ss:Cell>
      <ss:Cell>
        <ss:Data ss:Type="String"><xsl:value-of select="current()/@id"/></ss:Data>
      </ss:Cell>
      <ss:Cell>
        <ss:Data ss:Type="String"><xsl:value-of select="Year"/></ss:Data>
      </ss:Cell>
      <ss:Cell>
        <ss:Data ss:Type="Number"><xsl:value-of select="Periods/P1"/></ss:Data>
      </ss:Cell>
      <ss:Cell>
        <ss:Data ss:Type="Number"><xsl:value-of select="Periods/P2"/></ss:Data>
      </ss:Cell>
      <ss:Cell>
        <ss:Data ss:Type="Number"><xsl:value-of select="Periods/P3"/></ss:Data>
      </ss:Cell>
      <ss:Cell>
        <ss:Data ss:Type="Number"><xsl:value-of select="Periods/P4"/></ss:Data>
      </ss:Cell>
		</ss:Row>
	</xsl:template>

</xsl:stylesheet>