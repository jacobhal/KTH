<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns="http://www.w3.org/1999/xhtml">

  <xsl:output method="xml"/>

  <xsl:variable name="ver"><xsl:value-of select="page/version"/></xsl:variable>
  <xsl:variable name="auth"><xsl:value-of select="page/author"/></xsl:variable>

  
  <xsl:template match="page">
    <html xmlns="http://www.w3.org/1999/xhtml">
    <head>
      <title><xsl:value-of select="title"/></title>
      <meta name="author" content="{$auth}"/>
      <meta name="version" content="{$ver}"/>
      <meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1">
    </head>
    
      <body>
        <h1>Nyheter</h1>
        <xsl:apply-templates select="newscolumn" />
      </body>
    </html>
  </xsl:template>

  <xsl:template match="newscolumn">
    <ul>
        <xsl:apply-templates select="news" />
    </ul>
  </xsl:template>

  <xsl:template match="news">
    <li>
      <xsl:variable name="href"><xsl:value-of select="link"/></xsl:variable> 
      <a href="{$href}"><strong><xsl:value-of select="title"/></strong></a>
      - 
      <strong><xsl:apply-templates select="date" /></strong>
      <xsl:value-of select="content"/>
      
    </li>

  </xsl:template>

  <xsl:template match="date">
    <xsl:value-of select="day"/>&#160;
    <xsl:value-of select="month"/>&#160;
    <xsl:value-of select="year"/>
  </xsl:template>
      

</xsl:stylesheet>

