#include"Component.h"
#include"Actor.h"
Component::Component() {

}
Component::~Component() {

}
Component::Component(Ptr<Actor> _mactorptr) {
	mactorptr = _mactorptr;
}
__int8 Component::GetPriority() const {
	return mpriority;
}
bool Component::operator>(Component const& r) {
	return this->mpriority > r.mpriority;
}
bool Component::operator<(Component const& r) {
	return this->mpriority < r.mpriority;
}


Transform Component::GetTransform() const {
	return mactorptr.lock()->GetTransform();
}
