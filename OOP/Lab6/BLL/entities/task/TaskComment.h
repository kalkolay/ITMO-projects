#pragma once

#include "../collaborator/CollaboratorSystem.h"

namespace reports::entities
{
    class TaskComment
    {
    public:
        TaskComment(Collaborator* author,
                    std::string   comment);

        [[nodiscard]] Collaborator* GetAuthor () const;
        [[nodiscard]] std::string   GetComment() const;

    private:
        Collaborator* m_author;
        std::string   m_comment;
    };
}