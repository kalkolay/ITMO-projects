#include "TaskComment.h"

namespace reports::entities
{
    TaskComment::TaskComment(Collaborator* author,
                             std::string   comment)
        : m_author ( author )
        , m_comment( std::move(comment) )
    {}

    Collaborator* TaskComment::GetAuthor() const
    {
        return m_author;
    }

    std::string TaskComment::GetComment() const
    {
        return m_comment;
    }
}