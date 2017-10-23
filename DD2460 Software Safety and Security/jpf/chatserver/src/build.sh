#!/bin/sh

[ -e "${JPF_HOME}" ] || JPF_HOME="${HOME}/jpf/jpf-core"

javac -classpath ${JPF_HOME}/build/jpf.jar:. \
	env/java/*/*.java # env/java/*/*/*.java
# uncomment the last part if you write a model class for
# java.util.concurrent.ThreadPoolExecutor.java.
javac -Xbootclasspath/p:env -classpath ${JPF_HOME}/build/jpf.jar:. \
	*.java
