import psycopg2

conn = psycopg2.connect(
    host="localhost",
    database="library",
    user="postres",
    password="20042102"
)

# Начинаем транзакцию
with conn, conn.cursor() as cursor:

    book_id = 3
    
    # Получаем список читателей, стоящих в очереди на эту книгу
    cursor.execute("SELECT reader_id FROM book_queue WHERE book_id = %s", (book_id,))
    queue = [row[0] for row in cursor.fetchall()]
    
    # Если очередь не пуста, выдаем книгу первому читателю в очереди
    if queue:
        reader_id = queue[0]
        cursor.execute("INSERT INTO lending_history (reader_id, book_id, lending_date) VALUES (%s, %s, NOW())", (reader_id, book_id))
        cursor.execute("DELETE FROM book_queue WHERE book_id = %s AND reader_id = %s", (book_id, reader_id))
        
        # Если у читателя в очереди остались еще книги, добавляем их в начало очереди
        remaining_books = queue[1:]
        if remaining_books:
            remaining_books = remaining_books[:3]
            cursor.execute("INSERT INTO book_queue (reader_id, book_id) VALUES " + ", ".join(["(%s, %s)"] * len(remaining_books)), [(reader_id, book_id) for book_id in remaining_books])
        
    # Если очередь пуста, ничего не делаем
    
    # Заканчиваем транзакцию
    conn.commit()

