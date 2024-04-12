alter session set optimizer_adaptive_features=false;

SELECT DISTINCT title, fee
FROM EDU_VIDEO.VIDEOS
WHERE duration BETWEEN 120 AND 150;


SELECT video_code, title, fee
FROM EDU_VIDEO_INDEX.VIDEOS
WHERE duration = 120 AND fee = 516;