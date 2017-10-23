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
			<th>Total</th>
			<th></th>
			<th></th>
		</tr>
		<xsl:apply-templates/>
	</table>
	<xsl:call-template name="total"/>
</xsl:template>

<xsl:template match="Course">

	<xsl:variable name="id"><xsl:value-of select="current()/@id"/></xsl:variable>
	<tr>
		<td>
			<a href='{Link}'><xsl:value-of select="Name"/></a>
		</td>
		<td><xsl:value-of select="$id"/></td>
		<td><xsl:value-of select="Year"/></td>
		<td><xsl:value-of select="Periods/P1"/></td>
		<td><xsl:value-of select="Periods/P2"/></td>
		<td><xsl:value-of select="Periods/P3"/></td>
		<td><xsl:value-of select="Periods/P4"/></td>
		<td><xsl:value-of select="Periods/P1 + Periods/P2 + Periods/P3 + Periods/P4"/> HP</td>
		<td>
			<a href='changeCourse.php?id={$id}&amp;name={Name}&amp;year={Year}&amp;p1={Periods/P1}&amp;p2={Periods/P2}&amp;p3={Periods/P3}&amp;p4={Periods/P4}&amp;link={Link}'>Ändra</a>
		</td>
		<td>
			<a href='delete.php?id={$id}'>X</a>
		</td>
	</tr>
</xsl:template>

<xsl:template name="total">
	Totalt antal högskolepoäng: <b><xsl:value-of select="sum(//Periods/P1) +  sum(//Periods/P2) + sum(//Periods/P3) + sum(//Periods/P4)"/></b>
</xsl:template>

</xsl:stylesheet>