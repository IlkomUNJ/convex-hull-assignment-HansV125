[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/1PRAkQnI)
# Identity
Name : Hansen Nathaniel 1313623071

# AI usage
I used Gemini AI mainly to explain the algorithm that is used in the deberg book and also how to find the direction of a point (is it left or right to my current point) in which the AI gave me the formula for orientation determinant which is proven to be useful. other minor earlier usage is how to use QT specific modifiers like QPushButton and QVBoxLayout and QHBoxLayout, basically the QT documentations.
my main queries are as follow:

•  "Algorithm SLOWCONVEXHULL(P)
   Input. A set P of points in the plane.
   Output. A list L containing the vertices of CH(P) in clockwise order.
   1. E ←/0.
   2. for all ordered pairs (p,q) ∈ P×P with p not equal to q
   3. do valid ←true
   4. for all points r ∈ P not equal to p or q
   5. do if r lies to the left of the directed line from p to q
   6. then valid ← false.
   7. if valid then Add the directed edge →pq to E.
   8. From the set E of edges construct a list L of vertices of CH(P), sorted in clockwise order.
   Can you explain this algorithm"
• "can you explain the formula to find the direction of point whether it's clockwise or counter"
• "my iteration checks shows 37, but it's not o(n^3) how much orientation check would 5 points have then on paper"
• "Algorithm CONVEXHULL(P)
   Input. A set P of points in the plane.
   Output. A list containing the vertices of CH(P) in clockwise order.
   1.  Sort the points by x-coordinate, resulting in a sequence p1,...,pn.
   2.  Put the points p1 and p2 in a list Lupper, with p1 as the first point.
   3.  for i ←3 to n
   4.  do Append pi to Lupper.
   5.  while Lupper contains more than two points and the last three points in Lupper do not make a right turn
   6.  do Delete the middle of the last three points from Lupper.
   7.  Put the points pn and pn−1 in a list Llower, with pn as the first point.
   8.  for i ←n−2 downto 1
   9.  do Append pi to Llower.
   10.  while Llower contains more than 2 points and the last three points in Llower do not make a right turn
   11. do Delete the middle of the last three points from Llower.
   12. Remove the first and the last point from Llower to avoid duplication of the points where the upper and lower hull meet.
   13. Append Llower to Lupper, and call the resulting list L.
   14. return L
   now how about explaining this algorithm"

# Collaboration usage
I collaborated with Deric Navino. given that he didn't fully read the assignment text, he initially only worked on the Convex Hull calculation, the one which calculates lower and upper hull first then connects it. While i, only has done the Slow Convex Hull calculation. given the mutual need, we both decided to showcase each other our work and explained how the program and the inner calculations worked and how the hull is built and how the algorithm differs. the point being, our collaboration is focused on filling each other in the understanding of the algorithm we haven't worked on at the time. 

# Commit Rules
Use .gitignore to stripe any binaries from the resulting build before commit.  If you cloned directly from the template, you are safe. 

# Due Time
September 30th, 2025. 23: 59 WIB
