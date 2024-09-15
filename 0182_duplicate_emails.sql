SELECT 
    email AS 'Email'
From Person
GROUP BY email
HAVING COUNT(email) > 1