## Auth (TODO)

| Метод                                          | Описание                        | Возвращает                     |
| ---------------------------------------------- | ------------------------------- | ------------------------------ |
| `registerUser(handle, display_name, password)` | Регистрация нового пользователя | `bool`             |
| `loginUser(handle, password)`                  | Авторизация    | `User?`               |

---

## Users (TODO)

| Метод                                                              | Описание                            | Возвращает     |
| ------------------------------------------------------------------ | ----------------------------------- | -------------- |
| `getUserById(user_id)`                                             | Получить пользователя по ID         | `User?`        |
| `getUserByHandle(handle)`                                          | Поиск по @handle                    | `User?`        |
| `getUsersByIds(vector<id>)`                                        | Batch-загрузка пользователей        | `vector<User>` |
| `searchUsers(query, limit)`                                        | Поиск пользователей по имени/handle | `vector<User>` |
| `updateUserProfile(user_id, display_name?, avatar?, description?)` | Обновить профиль                    | `bool`         |

---

## Chats (TODO)

| Метод                                                   | Описание                                   | Возвращает            |
| ------------------------------------------------------- | ------------------------------------------ | --------------------- |
| `getChatById(chat_id)`                                  | Получить чат по ID                         | `Chat?`               |
| `getUserChats(user_id)`                                 | Список чатов пользователя                  | `vector<ChatPreview>` |
| `getOrCreateDirectChat(user1_id, user2_id)`             | Получить или создать личку (идемпотентно!) | `Chat`                |
| `createGroupChat(name, creator_id, member_ids(vector<id>))`         | Создать групповой чат                      | `Chat`                |
| `getChatMembers(chat_id)`                               | Список участников чата                     | `vector<ChatMember>`  |
| `addChatMember(chat_id, user_id, role)`                 | Добавить участника                         | `bool`                |
| `removeChatMember(chat_id, user_id)`                    | Удалить участника                          | `bool`                |
| `updateMemberRole(chat_id, user_id, new_role)`          | Изменить роль участника                    | `bool`                |
| `updateChatInfo(chat_id, name?, avatar?, description?)` | Обновить инфо чата                         | `bool`                |

### ChatPreview (TODO)

При загрузке чата возвращаем не просто Chat, а ChatPreview с последним сообщением(текст, автор), списком непрочитанных и тд.

---

## Messages (TODO)

| Метод                                                                | Описание                      | Возвращает        |
| -------------------------------------------------------------------- | ----------------------------- | ----------------- |
| `getMessageById(message_id)`                                         | Получить сообщение            | `Message?`        |
| `getChatMessages(chat_id, before_id?, limit)`                        | Сообщения чата с пагинацией   | `vector<Message>` |
| `sendMessage(chat_id, sender_id, text, reply_to_id?, forward_info?)` | Отправить сообщение           | `Message`         |
| `editMessage(message_id, new_text)`                                  | Редактировать сообщение       | `bool`            |
| `deleteMessage(message_id)`                                          | Удалить сообщение             | `bool`            |
| `markAsRead(chat_id, user_id, last_read_message_id)`                 | Обновить last_read_message_id | `void`            |
| `pollMessages(user_id)`                 | Вернуть список новых сообщений | `vector<Message>`            |

Пагинация через before_id` + `limit`

---

## Channels (TODO)

| Метод                                                         | Описание                                 | Возвращает              |
| ------------------------------------------------------------- | ---------------------------------------- | ----------------------- |
| `getChannelById(channel_id)`                                  | Получить канал по ID                     | `Channel?`              |
| `getChannelByHandle(handle)`                                  | Получить канал по @handle                | `Channel?`              |
| `getUserChannels(user_id)`                                    | Каналы, на которые подписан пользователь | `vector<Channel>`       |
| `createChannel(handle, name, owner_id, is_private?)`          | Создать канал                            | `Channel`               |
| `getChannelMembers(channel_id, offset?, limit?)`              | Подписчики канала                        | `vector<ChannelMember>` |
| `getChannelMemberCount(channel_id)`                           | Количество подписчиков                   | `int64`                 |
| `joinChannel(channel_id, user_id)`                            | Подписаться на канал                     | `bool`                  |
| `leaveChannel(channel_id, user_id)`                           | Отписаться от канала                     | `bool`                  |
| `updateChannelInfo(channel_id, name?, avatar?, description?)` | Обновить инфо канала                     | `bool`                  |

---

## Posts (TODO)

| Метод                                                   | Описание                    | Возвращает     |
| ------------------------------------------------------- | --------------------------- | -------------- |
| `getPostById(post_id)`                                  | Получить пост               | `Post?`        |
| `getChannelPosts(channel_id, before_id?, limit)`        | Посты канала                | `vector<Post>` |
| `createChannelPost(channel_id, text, enable_comments?)` | Создать пост в канале       | `Post`         |
| `editPost(post_id, new_text)`                           | Редактировать пост          | `bool`         |
| `deletePost(post_id)`                                   | Удалить пост                | `bool`         |
| `pollPosts(user_id)`                 | Вернуть список новых постов | `vector<Post>`            |

### Комментарии

Комментарии реализованы как сообщения в discussion-чате(как в телеграме).
При создании канала автоматически создаётся его discussion-чат.
При создании поста с комментариями:
1. Создаётся сообщение(копия поста) в этом чате.
2. `discussion_message_id` в посте указывает на это сообщение

---

## Reactions (TODO)

| Метод                                            | Описание                       | Возвращает         |
| ------------------------------------------------ | ------------------------------ | ------------------ |
| `addMessageReaction(message_id, user_id, emoji)` | Поставить реакцию на сообщение | `Reaction`         |
| `addPostReaction(post_id, user_id, emoji)`       | Поставить реакцию на пост      | `Reaction`         |
| `removeReaction(reaction_id)`                    | Убрать реакцию                 | `bool`             |
| `getMessageReactions(message_id)`                | Реакции на сообщение           | `vector<Reaction>` |
| `getPostReactions(post_id)`                      | Реакции на пост                | `vector<Reaction>` |

---

## Attachments (TODO)

| Метод                                                               | Описание                      | Возвращает           |
| ------------------------------------------------------------------- | ----------------------------- | -------------------- |
| `addMessageAttachment(message_id, file_type, file_size, file_path)` | Добавить вложение к сообщению | `Attachment`         |
| `addPostAttachment(post_id, file_type, file_size, file_path)`       | Добавить вложение к посту     | `Attachment`         |
| `getMessageAttachments(message_id)`                                 | Вложения сообщения            | `vector<Attachment>` |
| `getPostAttachments(post_id)`                                       | Вложения поста                | `vector<Attachment>` |
| `deleteAttachment(attachment_id)`                                   | Удалить вложение              | `bool`               |
