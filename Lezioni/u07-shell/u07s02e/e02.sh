#!/bin/bash

# Questo script:
#   pulisce il terminal2
#   mostra un saluto
#   fornisce informazioni sugli utenti attualmente connessi
#   imposta e visualizza due variabili locali di shell

clear

echo "Ciao, $USER!"
echo

echo "Elenco utenti connessi"
w

echo "Assegna due variabili locali di shell"
COLORE="nero"
VALORE="9"

echo "Stringa: $COLORE"
echo "Numero: $VALORE"
echo

echo "Ora restituisco il controllo"
echo