        var bindEventToList = function (rootSelector, selector, callback, eventName) {
            var eName = eventName || 'click';
            $(rootSelector).on(eName, selector, function () {
                var project = ko.dataFor(this);
                callback(project);
                return false;
            });

        };
