#include "map/notifications/notification_queue.hpp"

#include "base/assert.hpp"

namespace notifications
{
NotificationCandidate::NotificationCandidate(eye::MapObject const & poi,
                                             std::string const & address)
: m_type(NotificationCandidate::Type::UgcReview)
, m_created(Clock::now())
, m_mapObject(std::make_shared<eye::MapObject>(poi))
, m_address(address)
{
  CHECK(!poi.IsEmpty(), ());

  m_mapObject->GetEditableEvents().clear();
}

NotificationCandidate::Type NotificationCandidate::GetType() const
{
  return m_type;
}

Time NotificationCandidate::GetCreatedTime() const
{
  return m_created;
}

Time NotificationCandidate::GetLastUsedTime() const
{
  return m_used;
}

bool NotificationCandidate::IsUsed() const
{
  return m_used.time_since_epoch().count() != 0;
}

void NotificationCandidate::MarkAsUsed()
{
  CHECK_EQUAL(m_used.time_since_epoch().count(), 0, ());

  m_used = Clock::now();
}

bool NotificationCandidate::IsSameMapObject(eye::MapObject const & rhs) const
{
  CHECK_EQUAL(m_type, NotificationCandidate::Type::UgcReview, ());

  return m_mapObject->AlmostEquals(rhs);
}

std::string const & NotificationCandidate::GetBestFeatureType() const
{
  CHECK_EQUAL(m_type, NotificationCandidate::Type::UgcReview, ());

  return m_mapObject->GetBestType();
}

m2::PointD const & NotificationCandidate::GetPos() const
{
  CHECK_EQUAL(m_type, NotificationCandidate::Type::UgcReview, ());

  return m_mapObject->GetPos();
}

std::string const & NotificationCandidate::GetDefaultName() const
{
  CHECK_EQUAL(m_type, NotificationCandidate::Type::UgcReview, ());

  return m_mapObject->GetDefaultName();
}

std::string const & NotificationCandidate::GetReadableName() const
{
  CHECK_EQUAL(m_type, NotificationCandidate::Type::UgcReview, ());

  return m_mapObject->GetReadableName();
}

std::string const & NotificationCandidate::GetAddress() const
{
  CHECK_EQUAL(m_type, NotificationCandidate::Type::UgcReview, ());

  return m_address;
}
}  // namespace notifications
