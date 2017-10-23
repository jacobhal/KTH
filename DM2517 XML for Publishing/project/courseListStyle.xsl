<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" indent="yes"/>

<xsl:template match="CourseList">
	<table style="width:100%">
		<tr>
			<th>Namn</th>
			<th>Kurskod</th>
			<th>Läsår</th>
			<th>P1</th>
			<th>P2</th>
			<th>P3</th>
			<th>P4</th>
		</tr>
		<xsl:apply-templates/>
	</table>
</xsl:template>

<xsl:template match="Course">
	<tr>
		<td><xsl:value-of select="Name"/></td>
		<td><xsl:value-of select="current()/@id"/></td>
		<td><xsl:value-of select="Year"/></td>
		<td><xsl:value-of select="Periods/P1"/></td>
		<td><xsl:value-of select="Periods/P2"/></td>
		<td><xsl:value-of select="Periods/P3"/></td>
		<td><xsl:value-of select="Periods/P4"/></td>
	</tr>
</xsl:template>

</xsl:stylesheet>