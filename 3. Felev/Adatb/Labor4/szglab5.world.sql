INSERT INTO members(member_code, name, address, dateofbirth, levelofmember)
VALUES('RA01', 'Rittgasszer Ákos', '2000 Szentendre, Kussuth u. 17', date'1999-11-24', 'BASIC');

UPDATE videos
SET duration = 155, fee = 500
WHERE video_code = 'GLAD001';

UPDATE videos
SET fee = fee - 50
WHERE appearance < '1984-03-15' AND duration > 150;

UPDATE loans
SET loans.discount = 15
WHERE loans.discount = 0 AND loans.member_id IN    (SELECT members.member_id
                                                    FROM members
                                                    WHERE levelofmember = 'BASIC');
                                                    
DELETE FROM loans
WHERE loans.dateofturnback < date'2017-01-01';

INSERT INTO loans(video_id, member_id, dateofcreation)
(SELECT videos.video_id, members.member_id, SYSDATE() as dateofcreation
FROM videos, members
WHERE members.name = 'Rittgasszer Ákos' AND videos.video_code = 'ELEM005');

INSERT INTO loans(video_id, member_id, dateofcreation)
VALUES(
    (SELECT videos.video_id FROM videos WHERE videos.video_code = 'ELEM005'),
    (SELECT members.member_id FROM members WHERE members.name = 'Rittgasszer Ákos'),
    (date'2019-01-01')
);