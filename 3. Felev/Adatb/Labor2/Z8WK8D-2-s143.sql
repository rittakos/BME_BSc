set echo off
set verify off
alter session set NLS_DATE_FORMAT='YYYY-MM-DD';
set serveroutput on
set feedback off

DROP TABLE tagok;
DROP TABLE lemez;

prompt <tasks>

prompt <task n="1">
prompt <![CDATA[
    --Az elso feladathoz nem kell SQL kod
prompt ]]>
prompt </task>


prompt <task n="2">
prompt <![CDATA[

CREATE TABLE tagok(
    tagok_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    cim VARCHAR(100) NOT NULL,
    szuletes DATE NOT NULL,
    szint CHAR(6) NOT NULL,
    CONSTRAINT szint_check CHECK(szint = 'BASIC' OR szint = 'SILVER' OR szint = 'GOLD'),
    belepes DATE DEFAULT GETDATE(),
    CONSTRAINT belepes_check CHECK(belepes >= szuletes),
    kod CHAR(10) NOT NULL UNIQUE,
    nev VARCHAR(100) NOT NULL
);  

CREATE TABLE lemez(
    lemez_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    cim CHAR(50) NOT NULL,
    megjelenes DATE NOT NULL,
    CONSTRAINT megjelenes_check CHECK(megjelenes >= DATE'1848-03-15'),
    rendezo CHAR(100) NOT NULL,
    kolcsonzesi_dij NUMBER DEFAULT 135,
    CONSTRAINT kolcsonzesi_dij_check CHECK(kolcsonzesi_dij >= 50),
    tipus CHAR(7) NOT NULL,
    CONSTRAINT tipus_check CHECK(tipus = 'DVD' OR tipus = 'Blu-ray'),
    hossz DATE DEFAULT GETDATE(),
    CONSTRAINT hossz_check CHECK(hossz >= 15 AND hossz <= 270),
    kod CHAR(7) NOT NULL UNIQUE
);

CREATE TABLE kolcsonzi(
    kolcsonzi_id NUMBER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    elvitel DATE NOT NULL,
    visszahozatal DATE,
    CONSTRAINT visszahozatal_check CHECK(visszahozatal >= elvitel),
    kedvezmeny NUMBER DEFAULT 0,
    CONSTRAINT kedvezmeny_check CHECK(kedvezmeny >= 0 AND kedvezmeny <= 100),
    tag_kod CHAR(10) NOT NULL,
    CONSTRAINT tag_kod_kulso_kulcs FOREIGN KEY(tag_kod) REFERENCES tagok(tagok_id),
    lemez_kod CHAR(7) NOT NULL,
    CONSTRAINT lemez_kod_kulso_kulcs FOREIGN KEY(lemez_kod) REFERENCES lemez(lemez_id)
);
prompt ]]>
prompt </task>
    