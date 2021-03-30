## Help Stumpless Do Better, Suck Less
Stumpless aims to do a small thing well while staying as small as possible. If
you've got a problem with the project, you have a great idea for a new feature,
or you just want to find a way to contribute, then check out the guidelines
below on how to get started. Also, please make sure that you adhere to the
[Code of Conduct](CODE_OF_CONDUCT.md) however you participate.


### **I know what I'm doing**
If you're a regular user of the library and know it pretty well, you can give
back to the community just by helping out others who have a question. Head over
to the project's [gitter](https://gitter.im/stumpless/community) room and if
there is a question that you can help with, don't hesitate to jump in!


### **It broke**
If you've got a problem with the project, please make sure that you've done the
following things before submitting an issue:

 * Review the documentation to ensure that the behavior is unintentional
 * Search through the other issues on the project to ensure that this is not
   already captured
 * Replicate the problem from the latest version branch

If you've completed all of these steps and the problem persists, submit an issue
on the [GitHub project](https://github.com/goatshriek/stumpless) using the
provided issue template with all information filled in.

Even better: if you know how to fix the issue, go ahead and submit a pull
request using the provided template, mentioning the corresponding issue number.


### **I'm helping!**
Made some changes and want to share your work? Great! Submit a pull request and
we'll review it for inclusion into the latest version. Make sure that you follow
these guidelines:
 * If you're working on something that's relatively small, then you don't need
   to worry about the number of commits in your branch, as it will be squashed
   before it is merged into the `latest` branch. If you're working on something
   marked as a `good first issue` for example, don't worry about keeping a clean
   commit history and just focus on the fun stuff! You will be retained as the
   author of the commit, to make sure that contribution credit is reflected
   in the commit history and on GitHub.
 * If you're working on something larger, squashing it into a
   single commit might not make a lot of sense, and so the number of commits
   becomes more important. If you find yourself in this situation, try to make
   sure that each commit is logical and adds value to the commit history. If
   you need a little guidance to get started with adjusting the commit history
   of your change, check out
   [this chapter](https://git-scm.com/book/en/v2/Git-Tools-Rewriting-History)
   from the Git Book about it, which covers several common adjustments. Note
   that this scenario will be rare, and if you aren't sure if it applies to
   your change then you should ask before going down the complex and
   time-consuming path of rebasing.
 * If a commit resolves or is otherwise related to a particular issue, include
   a reference to it in the body of the commit.


### **It would be great if...**
If you have a new feature that you think would be worthwhile, please open an
issue on the github project using the 'Feature Request' template. If it fits
with the project then you can begin working on a fork and submit a pull
request of your branch so that we can watch it progress and merge it in once
it is complete. Or if you don't have time we will add it to the project
[roadmap](roadmap.md) and eventually implement it depending on other priorities.


### **I don't know where to start**
If you'd like to contribute but aren't quite sure where to start, take a look at
the issues and see if there is anything there that you think you can tackle! In
particular, the 'help wanted' and 'good first issue' labels mark issues that
need attention and are relatively simple to fix, respectively.

The [development notes](development.md) have a getting started section for
newcomers to the project, and are worth a read.


#### No, I mean I **really** don't know where to start
If you are brand new to the community at large and are looking for a little more
detail on how to contribute, then this section should help you get started.

Stumpless has a default branch named `latest` off of which all new feature
branches are based. Once all changes planned for the next version have been
implemented, a tag will be added for the commit named after the semantic version
number and the `release` branch will be updated to point to this commit. In this
way, `latest` always has the most up to date changes and `release` always points
to the last complete version released.

To create your own feature or update, you should fork the repository and create
a new branch based on the `latest` branch. Don't forget to update the ChangeLog
with your changes, and when you're ready open a pull request against `latest`.

It is unusual, but you may find that it is more appropriate to base your branch
on the `release` branch instead of `latest`. Some examples of these types of
changes are:
 * updates to project documentation that is relevant to the current version of
   the project as well as the next
 * patches that need to be applied to the current version of the library in
   order to fix broken functionality (note that this will require updating the
   library to the next patch level, for example from 1.3.2 to 1.3.3)

Be sure to check out the [dependencies](dependencies.md) list to make sure that
your development environment has all of the necessary tools. More specifically,
make sure that you are able to run the tests and development tools before you
make extensive changes, so that you can test iteratively as you go.

A detailed tutorial on the traditional git flow style of development is beyond
the scope of the project documentation, but the following guides serve as good
starting material:
 * [GitHub Guides](https://guides.github.com/introduction/flow/)
 * [Creating a Pull Request from a Fork](https://help.github.com/en/github/collaborating-with-issues-and-pull-requests/creating-a-pull-request-from-a-fork)

To recap, your basic steps will be to fork the repository, create a new branch
based on `latest` (or perhaps `release` depending on the circumstances), and
when you are finished adding commits to it create a pull request back to the
main repository.


### You still there?
The project team aims to be as responsive as we can, typically responding to
new issues and pull requests within a few days. Asking for clarification on an
issue or requesting changes to a pull request is fairly common, and often some
back and forth is needed before something can be accepted.

Unfortunately, sometimes these conversations stall and no progress is made. In
cases where this happens and the project team is waiting for a response, the
item will eventually be closed as stale. Items that have had no response for
two months will be labeled as stale, and a warning will be posted in the
discussion. If another month passes with no response, then the item will be
closed as stale.

Stale items can always be reopened, so don't feel like the discussion is over
forever if something gets closed! We just want to keep our active work nice
and tidy for everyone to quickly see what we're doing (and what we aren't).


## Thanks!
And no matter how you contribute, thanks for giving back to the community!

Stumpless Team

