<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" indent="yes"/>

<xsl:template match="/">
  <xsl:apply-templates/>
</xsl:template>

<!-- Table of contents subsection -->
<xsl:template match="report/body/h1/h2">
	<xsl:number format="1. " level="multiple" count="h1|h2"/>
	<a href="#{generate-id()}"><xsl:value-of select="current()/@title"/></a><br/>
	<xsl:apply-templates select="h3"/>
</xsl:template>

<!-- Table of contents subsubsection -->
<xsl:template match="report/body/h1/h2/h3">
	<xsl:number format="1. " level="multiple" count="h1|h2|h3"/>
	<a href="#{generate-id()}"><xsl:value-of select="current()/@title"/></a><br/>
</xsl:template>

<!-- Content subsection -->
<xsl:template name="subsection">
	<a name="{generate-id()}"></a>
	<h3>
		<xsl:number format="1. " level="multiple" count="h1|h2"/>
		<xsl:value-of select="@title"/>
	</h3>
	<xsl:for-each select="p">
		<p>
			<xsl:value-of select="current()"/>
		</p>
	</xsl:for-each>
	<xsl:for-each select="h3">
		<xsl:call-template name="subsubsection"/>
	</xsl:for-each>
</xsl:template>

<!-- Content subsubsection -->
<xsl:template name="subsubsection">
	<a name="{generate-id()}"></a>
	<h4>
		<xsl:number format="1. " level="multiple" count="h1|h2|h3"/>
		<xsl:value-of select="@title"/>
	</h4>
	<xsl:for-each select="p">
		<p>
			<xsl:value-of select="current()"/>
		</p>
	</xsl:for-each>
</xsl:template>

<xsl:template match="report">
  <html>
  	<head>
  		<META http-equiv="Content-Type" content="text/html; charset=UTF-8"/>
  		<title><xsl:value-of select="head/title"/></title>
  	</head>
  	<body>
  		<h1><xsl:value-of select="head/title"/></h1>
  		<p>Authors: 
  			<xsl:for-each select="head/authors/author">
  				<xsl:value-of select="current()"/>
  				<xsl:if test="not(position()=last())">,&#160;</xsl:if>
  			</xsl:for-each>
  		</p>
  		<p>Keywords: 
  			<xsl:for-each select="head/keywords/keyword">
  				<xsl:value-of select="current()"/>
  				<xsl:if test="not(position()=last())">,&#160;</xsl:if>
  			</xsl:for-each>
  		</p>
  		<!-- Table of contents -->
  		<p>
  			<xsl:for-each select="body/h1">
  				<xsl:number format="1. " level="multiple" count="h1"/>
  				<a href="#{generate-id()}"><xsl:value-of select="current()/@title"/></a>
				<br/>
				<!-- Handle subsections -->
				<xsl:apply-templates select="h2"/>
  			</xsl:for-each>
  		</p>

  		<!-- Actual content -->
  		<xsl:for-each select="body/h1">
			<a name="{generate-id()}"></a>
			<h2>
				<xsl:number format="1. " level="multiple" count="h1"/>
				<xsl:value-of select="current()/@title"/>
			</h2>
			<xsl:for-each select="p">
				<p>
					<xsl:value-of select="current()"/>
				</p>
			</xsl:for-each>
			<!-- Handle subsections-->
			<xsl:for-each select="h2">
				<xsl:call-template name="subsection"/>
			</xsl:for-each>
			
		
		</xsl:for-each>
  	</body>
  </html>
</xsl:template>
</xsl:stylesheet>