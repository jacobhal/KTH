<xsl:stylesheet version="1.0"
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="html"/>
	<xsl:template match="/ELECTION//ELECTORAL">
  		<p><xsl:value-of select="@NAME"/></p>
	</xsl:template>
</xsl:stylesheet>