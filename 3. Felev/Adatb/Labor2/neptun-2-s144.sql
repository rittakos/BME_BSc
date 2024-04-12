set echo off
set verify off
alter session set NLS_DATE_FORMAT='YYYY-MM-DD';
set serveroutput on
set feedback off

DROP TABLE megrendelesek;
DROP TABLE eszkozok;
DROP TABLE rendezvenyek;

prompt <tasks>

prompt <task n="1.1">
prompt <![CDATA[

prompt ]]>
prompt </task>

prompt <task n="2.1">
prompt <![CDATA[
CREATE TABLE eszkozok(
eszkoz_id NUMBER(3) NOT NULL,
nev CHAR(40) NOT NULL,
marka CHAR(20) NOT NULL,
tipus CHAR(15) NOT NULL,
CHECK(tipus='hang' OR tipus='feny' OR tipus='latvany' OR tipus='dekoracio' OR tipus='szorakoztato'),
gyartasi_szam NUMBER(20) NOT NULL,
koltseg NUMBER(6) DEFAULT 48000,
CHECK(koltseg>=15000 AND koltseg=600000),
megv_datuma DATE NOT NULL,
CHECK(megv_datuma>= TO_DATE('2008-01-01','YYYY-MM-DD')),
PRIMARY KEY(eszkoz_id)
);
prompt ]]>
prompt </task>

prompt <task n="2.2">
prompt <![CDATA[
CREATE TABLE rendezvenyek(
kod NUMBER(10) NOT NULL,
rendezveny_id NUMBER(3) NOT NULL,
megrendelo CHAR(40) NOT NULL,
rend_datum DATE NOT NULL,
CHECK(rend_datum>=TO_DATE('2017-01-01','YYYY-MM-DD')),
helyszin CHAR(50) NOT NULL,
napszak CHAR(10) NOT NULL,
CHECK(napszak='nappal' OR napszak='ejszaka'),
orzes CHAR(5) NOT NULL,
CHECK((napszak='ejszaka' AND orzes='igen') OR orzes='nem'),
zene CHAR(5) NOT NULL,
CHECK(zene='igen' OR zene='nem'),
keretosszeg NUMBER(10) NOT NULL,
CHECK(keretosszeg>=60000),
vendeg_szam NUMBER(4),
PRIMARY KEY (rendezveny_id)
);
prompt ]]>
prompt </task>

prompt <task n="2.3">
prompt <![CDATA[
CREATE TABLE megrendelesek(
megrendeles_id NUMBER (3) NOT NULL,
eszkoz_id NUMBER (3) NOT NULL,
rendezveny_id NUMBER (3) NOT NULL,
felelos CHAR(20) NOT NULL,
szallitas CHAR(10) DEFAULT 'auto',
CHECK(szallitas='hajo' OR szallitas='busz' OR szallitas='gyalog' OR szallitas='auto' OR szallitas='egyeb'),
komment LONG,
PRIMARY KEY(megrendeles_id),
FOREIGN KEY(eszkoz_id) REFERENCES ESZKOZOK(eszkoz_id),
FOREIGN KEY(rendezveny_id) REFERENCES RENDEZVENYEK(rendezveny_id)
);
prompt ]]>
prompt </task>

prompt <task n="3.1">
prompt <![CDATA[

prompt ]]>
prompt </task>
prompt </tasks>