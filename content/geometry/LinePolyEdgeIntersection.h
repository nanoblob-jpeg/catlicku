/**
 * Author: thomas :V
 * Date: 2024-05-08
 * License: NA
 * Source: thomas
 * Description:  For use in computing line-polygon intersection between some line s-e and polygon side p1-p2. 
 *               To use, apply this function to all polygon edges, sort outputs by first key and maintain running sum of second key. 
 *               Segments for which the running sum was nonzero are in the polygon.
 */
vector<pair<P, ll>> linePoly(P s, P e, P p1, P p2) {
    ll s1 = sideOf(s,e,p1), s2 = sideOf(s,e,p2);
    if(s1==s2) return {};
    ll d = 1;
    if(s1*s2)d=2;
    if(s1<s2)d*=-1;
    return {{lineInter(s,e,p1,p2).second,d}};
}
