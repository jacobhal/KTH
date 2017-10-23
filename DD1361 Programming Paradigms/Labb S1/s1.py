# coding: utf-8
########################################################################
# Dessa funktioner är det som ska skrivas för att lösa de olika
# uppgifterna i labblydelsen.
########################################################################

def dna():          # uppgift 1
    return r"^[ACGT]+$"

def sorted():       # uppgift 2
    # Non-capturing group (?:) does not capture the things it matches, it's just an assertion, back-referencing to such a pattern is not allowed.
    return r"^(?:(\d)\1*|9*8*7*6*5*4*3*2*1*0*)$"

def hidden1(x):     # uppgift 3
    # indata x är strängen som vi vill konstruera ett regex för att söka efter
    #regex = r"\w*" + re.escape(x) + r"\w*"
    return x

def hidden2(x):     # uppgift 4
    # Kan uppgiften utökas och endast matcha så att gapet mellan de matchande bokstäverna är lika långt?
    # Tror inte det eftersom detta skulle i så fall kräva att man kom ihåg vad längden av gapet var första gången
    # och regex kan inte "minnas" på det sättet. Däremot skulle det nog funka att sätta en max/min gräns eller en statisk gräns för gapet.
    # Exempel på regex med fixerat gap då progp är indata: p.{3}r.{3}o.{3}g.{3}p

    # indata x är strängen som vi vill konstruera ett regex för att söka efter
    s = ".*"
    return s.join(x) # See if characters in x can be joined together by characters we don't care about.

def equation():     # uppgift 5
    # Kan equation och parantheses kombineras för att tillåta aritmetiska uttryck inom paranteserna?
    # Ja, detta går att lösa.
    # Regex: r"^(\(([-+]?\d+(?:[+/*\-]\d+)*(?:[=][+\-]?\d+)?(?:[+/*\-]\d+)*)?(\((\((\((\(\))*\))*\))*\))*\))+$"
    # Regexen ovan tillåter ett aritmetiskt uttryck då djupet av paranteserna endast är 1. Regexen för ekvationer
    # måste läggas till i varje djup för att det ska funka för flera paranteser.
    # Regexen för ekvationer omsluts som en egen grupp som är valbar, dvs. som följs av ett ? för att uttrycket fortfarande ska kunna matcha en tom parantes.
    
    return r"^[-+]?\d+(?:[+/*\-]\d+)*(?:[=][+\-]?\d+)?(?:[+/*\-]\d+)*$"

def parentheses():  # uppgift 6
    return r"^(\((\((\((\((\(\))*\))*\))*\))*\))+$"

def sorted3():      # uppgift 7
    # ^((?=\d{3}$)1?2?3?4?5?6?7?8?9?)$

    # Se regex ovan, skulle detta kunna fungera? Om detta inte är möjligt så går det naturligtvis att göra som nedan men
    # det skulle resultera i väldigt många uttryck inom gruppen vilket leder till att mycket backtracking kan ske.
    # En sådan lösning skulle bli både lång och ineffektiv.

    return r"^\d*(01[2-9]|[01]2[3-9]|[0-2]3[4-9]|[0-3]4[5-9]|[0-4]5[6-9]|[0-5]6[7-9]|[0-6]7[89]|[0-7]89)\d*$"


########################################################################
# Raderna nedan är lite testkod som du kan använda för att provköra
# dina regexar.  Koden definierar en main-metod som läser rader från
# standard input och kollar vilka av de olika regexarna som matchar
# indata-raden.  För de två hidden-uppgifterna används söksträngen
# x="test" (kan lätt ändras nedan).  Du behöver inte sätta dig in i hur
# koden nedan fungerar.
#
# För att provköra från terminal, kör:
# > python s1.py
# Skriv in teststrängar:
# [skriv något roligt]
# ...
########################################################################
from sys import stdin
import re

def main():
    def hidden1_test(): return hidden1('progp')
    def hidden2_test(): return hidden2('progp')
    tasks = [dna, sorted, hidden1_test, hidden2_test, equation, parentheses, sorted3]
    print('Skriv in teststrängar:')
    while True:
        line = stdin.readline().rstrip('\r\n')
        if line == '': break
        for task in tasks:
            result = '' if re.search(task(), line) else 'INTE ' 
            print('%s(): "%s" matchar %suttrycket "%s"' % (task.__name__, line, result, task()))
    

if __name__ == '__main__': main()

    