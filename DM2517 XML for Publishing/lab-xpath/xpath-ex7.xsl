<xsl:stylesheet version="1.0"
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="html"/>

	<xsl:template match="//VALID/PERSONELECTION[contains(@NAME,'R') and not(preceding::VALID[PERSONELECTION/@NAME = current()/@NAME])]">
  		<p><xsl:value-of select="@NAME"/></p>
	</xsl:template>

</xsl:stylesheet>