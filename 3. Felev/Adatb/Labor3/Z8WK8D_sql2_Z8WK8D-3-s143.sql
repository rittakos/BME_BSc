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

prompt <task n="2.1">
prompt <![CDATA[
SELECT *
FROM videos;
prompt ]]>
prompt </task>

prompt <task n="2.2">
prompt <![CDATA[
SELECT videos.video_code, videos.title, videos.director
FROM videos
WHERE videos.type = 'B';
prompt ]]>
prompt </task>

prompt <task n="2.3">
prompt <![CDATA[
SELECT videos.video_code, videos.title, loans.dateofcreation AS loan_date, loans.dateofturnback AS return_date, videos.appearance
FROM videos JOIN loans ON videos.video_id = loans.video_id
WHERE videos.appearance < '2000-01-01' 
ORDER BY loans.dateofcreation DESC, videos.title;
prompt ]]>
prompt </task>

prompt <task n="2.4">
prompt <![CDATA[
SELECT videos.video_code, videos.title, loans.dateofcreation AS loan_date
FROM videos JOIN loans ON videos.video_id = loans.video_id
WHERE videos.type = 'D' AND loans.dateofturnback IS NULL
ORDER by loans.dateofcreation DESC, videos.title;
prompt ]]>
prompt </task>

prompt <task n="2.5">
prompt <![CDATA[
SELECT videos.video_code, videos.title, loans.dateofcreation AS loan_date
FROM videos LEFT JOIN loans ON videos.video_id = loans.video_id
ORDER BY loans.loan_id, loans.dateofcreation DESC;
prompt ]]>
prompt </task>

prompt <task n="2.6">
prompt <![CDATA[
SELECT videos.video_code, videos.title, COUNT(loans.DATEOFCREATION) AS times
FROM videos LEFT JOIN loans ON videos.video_id = loans.video_id
GROUP BY videos.video_code, videos.title
ORDER BY videos.video_code;
prompt ]]>
prompt </task>

prompt <task n="2.7">
prompt <![CDATA[
SELECT videos.video_code, videos.title, COUNT(loans.DATEOFCREATION) AS times
FROM videos LEFT JOIN loans ON videos.video_id = loans.video_id
GROUP BY videos.video_code, videos.title
HAVING COUNT(loans.DATEOFCREATION) <= 1
ORDER BY videos.video_code;
prompt ]]>
prompt </task>

prompt <task n="2.8">
prompt <![CDATA[
SELECT videos.video_code, videos.title, NVL(NVL2(loans.dateofturnback, ' ', loans.dateofcreation), ' ') AS loan_date
FROM videos LEFT JOIN loans ON videos.video_id = loans.video_id
WHERE videos.type = 'D'
ORDER BY videos.title;
prompt ]]>
prompt </task>
prompt </tasks>