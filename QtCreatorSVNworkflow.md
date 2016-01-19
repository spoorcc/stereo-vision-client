#The basic workflow of using svn in Qt Creator.

# The typical work cycle #

## Update your working copy ##
_Tools > Subversion > Update repository_

If subversion is not showing in the tools menu, the file you're currently editing is probably not added to svn. Close the current file and go to something you're sure is part of the current repository like main.

## Make your changes ##
The most common changes that you'll make are edits to the contents of your existing files.

The following action are pretty easy trough the Linux terminal, for windhoos I have no idea...
But sometimes you need to add, remove, copy and move files and directories—the svn add, svn delete, svn copy, and svn move commands handle those sorts of structural changes within the working copy.

## Review your changes ##
_Tools > Subversion > Diff repository_

Now a document is opened where all the differences between your code and the local code is shown

## Fix your mistakes ##
Nobody's perfect, so as you review your changes, you may spot something that's not quite right. Sometimes the easiest way to fix a mistake is start all over again from scratch.

_Tools > Subversion > revert "filename.cpp/filename.h"_ returns it to the state it was when you downloaded it.

## Resolve any conflicts (merge others' changes) ##
In the time it takes you to make and review your changes, others might have made and published changes, too. You'll want to integrate their changes into your working copy to avoid the potential out-of-dateness scenarios when you attempt to publish your own.

_Tools > Subversion > Update repository_ is the way to do this.

If this results in local conflicts, you'll need to resolve those.
The easiest way is if you revert your file, update and add you changes (if they are still necessary).
Otherwise, open up google ( http://ariejan.net/2007/07/04/how-to-resolve-subversion-conflicts/ ), and search for svn resolve. Always consult with the author of the piece of code that conflicts with you code!

## Commit your changes ##
Make sure the program is still building and running before you commit!
_Tools > Subversion > Commit all Files_

You can type something in the empty textfield above. This will be added to the log. Leave some information about the things you've changed.

Now others can see your work, too!