set echo off
set verify off
alter session set NLS_DATE_FORMAT='YYYY-MM-DD';
set serveroutput on
set feedback off

prompt <tasks>

prompt <task n="1.1">
prompt <![CDATA[

prompt ]]>
prompt </task>

prompt <task n="3.1">
prompt <![CDATA[
INSERT INTO members(member_code, name, address, dateofbirth, levelofmember)
VALUES('RA01', 'Rittgasszer Ákos', '2000 Szentendre, Kussuth u. 17', date'1999-11-24', 'BASIC');
prompt ]]>
prompt </task>

prompt <task n="3.2">
prompt <![CDATA[
UPDATE videos
SET duration = 155, fee = 500
WHERE video_code = 'GLAD001';
prompt ]]>
prompt </task>

prompt <task n="3.3">
prompt <![CDATA[
UPDATE videos
SET fee = fee - 50
WHERE appearance < '1984-03-15' AND duration > 150;
prompt ]]>
prompt </task>

prompt <task n="3.4">
prompt <![CDATA[
UPDATE loans
SET loans.discount = 15
WHERE loans.discount = 0 AND loans.member_id IN    (SELECT members.member_id
                                                    FROM members
                                                    WHERE levelofmember = 'BASIC');
prompt ]]>
prompt </task>

prompt <task n="3.5">
prompt <![CDATA[
DELETE FROM loans
WHERE loans.dateofturnback < date'2017-01-01';
prompt ]]>
prompt </task>

prompt <task n="3.6">
prompt <![CDATA[
INSERT INTO loans(video_id, member_id, dateofcreation)
VALUES(
    (SELECT videos.video_id FROM videos WHERE videos.video_code = 'ELEM005'),
    (SELECT members.member_id FROM members WHERE members.name = 'Rittgasszer Ákos'),
    (date'2019-01-01')
);
prompt ]]>
prompt </task>
prompt </tasks>